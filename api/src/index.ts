import { cors } from "@elysiajs/cors";
import {
	type Signer,
	type Umi,
	createSignerFromKeypair,
	generateSigner,
	publicKey,
	signerIdentity,
} from "@metaplex-foundation/umi";
import { createUmi } from "@metaplex-foundation/umi-bundle-defaults";
import {
	create,
	createCollection,
	fetchCollection,
	mplCore,
	transferV1,
} from "@metaplex-foundation/mpl-core";
import { Elysia } from "elysia";

const isSolanaAddress = (value: string): boolean =>
	/^[1-9A-HJ-NP-Za-km-z]{32,44}$/.test(value);

const module_e_3_collection = "D4hXyFdWK9yUs3EVoi9VqzjvPpgim8GRYr4vtoUmuh2c";

async function readKeypairFromFile(umi: Umi, path: string): Promise<Signer> {
	const key = await Bun.file(path).json();
	const keypair = umi.eddsa.createKeypairFromSecretKey(Uint8Array.from(key));
	const signer = createSignerFromKeypair(umi, keypair);

	return signer;
}

const app = new Elysia()
	.use(cors())
	.get("/", () => ({ success: true }))
	// Dynamically creates metadata for collection and assets
	.get("/module/:module/:submodule/:idWithExtension", ({ params, set }) => {
		const { module, submodule, idWithExtension } = params;
		const [id, extension] = idWithExtension.split(".");

		if (
			extension !== "json" ||
			(isNaN(Number(id)) && id !== "collection")
		) {
			set.status = 404;
			return { message: "Not found", success: false };
		}

		if (id !== "collection") {
			return {
				name: `Empathy Module ${module}-${submodule} Certificate #${id}`,
				description: `Certificate for completing the Empathy Module ${module}-${submodule}`,
				image: `${process.env.AWS_ENDPOINT_URL_FULL}/nft-module-${module}-${submodule}.png`,
				attributes: [
					{ trait_type: "Module", value: module },
					{ trait_type: "Sub-Module", value: submodule },
				],
				properties: {
					files: {
						uri: `${process.env.AWS_ENDPOINT_URL_FULL}/nft-module-${module}-${submodule}.png`,
						type: "image/png",
						cdn: true,
					},
					category: "image",
				},
			};
		} else {
			return {
				name: `Empathy Module ${module}-${submodule} Certificates`,
				image: `${process.env.AWS_ENDPOINT_URL_FULL}/collection-module-${module}-${submodule}.png`,
			};
		}
	})
	.post(
		"/mint",
		async ({
			body,
			error,
		}: {
			body: { account: string };
			error: Function;
		}) => {
			if (!body.account) {
				return error(400, { message: "Account is required" });
			}
			if (!isSolanaAddress(body.account)) {
				return error(400, { message: "Invalid address" });
			}

			const umi = createUmi("https://api.devnet.solana.com").use(
				mplCore(),
			);
			const nftAuthority = await readKeypairFromFile(
				umi,
				"keys/nft_authority.json",
			);
			umi.use(signerIdentity(nftAuthority));

			const collection = await fetchCollection(
				umi,
				publicKey(module_e_3_collection),
			);
			const asset = generateSigner(umi);

			await create(umi, {
				asset,
				collection,
				name: `Empathy Module E-3 Certificate #${collection.currentSize + 1}`,
				uri: `https://empathy-7335.fly.dev/module/e/3/${collection.currentSize + 1}.json`,
			}).sendAndConfirm(umi);

			await transferV1(umi, {
				asset: asset.publicKey,
				collection: collection.publicKey,
				newOwner: publicKey(body.account),
			}).sendAndConfirm(umi);

			return { success: true };
		},
	)
	.listen(3000);

console.log(
	`🦊 Elysia is running at ${app.server?.hostname}:${app.server?.port}`,
);
