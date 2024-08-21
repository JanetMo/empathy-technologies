/** @type {import('tailwindcss').Config} */

import defaultTheme from "tailwindcss/defaultTheme";

export default {
	content: ["./index.html", "./src/**/*.tsx"],
	theme: {
		extend: {
			container: {
				center: true,
				padding: "1rem",
			},
			fontFamily: {
				sans: ["Public Sans", ...defaultTheme.fontFamily.sans],
				serif: ["Montagu Slab", ...defaultTheme.fontFamily.sans],
			},
		},
	},
	plugins: [],
};
