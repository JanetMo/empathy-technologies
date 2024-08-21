import { useWallet, WalletContextState } from "@solana/wallet-adapter-react";
import { WalletMultiButton } from "@solana/wallet-adapter-react-ui";
import bs58 from "bs58";
import nacl from "tweetnacl";
import { useEffect, useState } from "react";

async function verifyWalletAndMint(provider: WalletContextState) {
	if (!provider.publicKey || !provider.signMessage) {
		return false;
	}

	const message = "Verify your Solana wallet";
	const encodedMessage = new TextEncoder().encode(message);
	let signedMessage;
	try {
		signedMessage = await provider.signMessage(encodedMessage);
	} catch (error) {
		console.error(error);
		return false;
	}
	const signature = bs58.encode(signedMessage);
	const isVerified = nacl.sign.detached.verify(
		encodedMessage,
		bs58.decode(signature),
		provider.publicKey.toBytes(),
	);

	if (isVerified) {
		await fetch(`${import.meta.env.VITE_MINTAPI_URL}/mint`, {
			method: "POST",
			headers: {
				"Content-Type": "application/json",
			},
			body: JSON.stringify({
				account: provider.publicKey.toString(),
			}),
		});
		return true;
	}
}

function Claim() {
	const [isConnected, setIsConnected] = useState(false);
	const [isVerified, setIsVerified] = useState(false);
	const [isBusy, setIsBusy] = useState(false);
	const wallet = useWallet();
	useEffect(() => {
		setIsConnected(!!wallet.publicKey);
	}, [wallet.publicKey]);

	const handleVerifyClick = async () => {
		setIsBusy(true);
		const result = await verifyWalletAndMint(wallet);
		if (result) {
			setIsVerified(true);
		}
		setIsBusy(false);
	};

	return (
		<main className="flex items-center w-full h-full">
			<div className="container text-center">
				<h1 className="text-4xl font-serif">Module E-3</h1>
				<h2 className="text-2xl">Completed! ✅</h2>
				<div className="text-8xl">🙌</div>
				<p className="my-2">
					Well done, you deserve a lovely NFT to verify completion!
				</p>
				{!isVerified ? (
					<div>
						<p className="my-2">
							Connect and verify your Solana wallet, and we'll
							send it straight your way!
						</p>
						<div>
							<WalletMultiButton />
						</div>
						{isConnected && (
							<div className="my-4">
								<button
									disabled={isBusy}
									className="inline-flex items-center justify-center w-80 h-10 rounded bg-[#C6F0FF] text-sm disabled:opacity-50 disabled:cursor-not-allowed"
									onClick={handleVerifyClick}
								>
									{isBusy ? (
										<>
											<svg
												xmlns="http://www.w3.org/2000/svg"
												width="24"
												height="24"
												viewBox="0 0 24 24"
												fill="none"
												stroke="currentColor"
												stroke-width="2"
												stroke-linecap="round"
												stroke-linejoin="round"
												className="animate-spin mr-2"
											>
												<path d="M21 12a9 9 0 1 1-6.219-8.56" />
											</svg>
											Minting..
										</>
									) : (
										<>Verify & Claim NFT</>
									)}
								</button>
							</div>
						)}
					</div>
				) : (
					<p className="my-2 text-center">
						Thank you! ❤️
						<br />
						The NFT is now in your wallet.
					</p>
				)}
			</div>
		</main>
	);
}

export { Claim };
