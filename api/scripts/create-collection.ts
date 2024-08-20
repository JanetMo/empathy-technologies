import {
	type Signer,
	type Umi,
	createSignerFromKeypair,
	generateSigner,
	signerIdentity,
} from "@metaplex-foundation/umi";
import { createUmi } from "@metaplex-foundation/umi-bundle-defaults";
import { createCollection, mplCore } from "@metaplex-foundation/mpl-core";

async function readKeypairFromFile(umi: Umi, path: string): Promise<Signer> {
	const key = await Bun.file(path).json();
	const keypair = umi.eddsa.createKeypairFromSecretKey(Uint8Array.from(key));
	const signer = createSignerFromKeypair(umi, keypair);

	return signer;
}

async function setupCollection() {
	const umi = createUmi("https://api.devnet.solana.com").use(mplCore());

	const signer = await readKeypairFromFile(umi, "keys/nft_authority.json");
	umi.use(signerIdentity(signer));

	const collection = generateSigner(umi);

	await createCollection(umi, {
		collection,
		name: "Empathy Module 2-6 Certificates",
		uri: "https://empathy-7335.fly.dev/module/2/6/collection.json",
	}).sendAndConfirm(umi);

	console.log(collection.publicKey.toString());
}

(async function main() {
	await setupCollection();
})();
