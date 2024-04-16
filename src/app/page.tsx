import { HomeContainer } from "@/components/container/home";
import Script from "next/script";

export default function Home() {
  return (
    <>
      <Script src="/wasm/heic-decoder.js" strategy="beforeInteractive" />
      <HomeContainer />
    </>
  );
}
