import {
	type Signer,
	type Umi,
	createSignerFromKeypair,
	generateSigner,
	publicKey,
	signerIdentity,
} from "@metaplex-foundation/umi";
import { createUmi } from "@metaplex-foundation/umi-bundle-defaults";
import { mplCore, updateCollection } from "@metaplex-foundation/mpl-core";

async function readKeypairFromFile(umi: Umi, path: string): Promise<Signer> {
	const key = await Bun.file(path).json();
	const keypair = umi.eddsa.createKeypairFromSecretKey(Uint8Array.from(key));
	const signer = createSignerFromKeypair(umi, keypair);

	return signer;
}

async function changeCollection() {
	const umi = createUmi("https://api.devnet.solana.com").use(mplCore());

	const signer = await readKeypairFromFile(umi, "keys/nft_authority.json");
	umi.use(signerIdentity(signer));

	await updateCollection(umi, {
		collection: publicKey("D4hXyFdWK9yUs3EVoi9VqzjvPpgim8GRYr4vtoUmuh2c"),
		name: "Empathy Module E-3 Certificates",
		uri: "https://empathy-7335.fly.dev/module/e/3/collection.json",
	}).sendAndConfirm(umi);

	console.log("OK!");
}

(async function main() {
	await changeCollection();
})();
