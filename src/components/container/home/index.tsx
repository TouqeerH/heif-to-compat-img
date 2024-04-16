"use client";
import Image from "next/image";
import { FormEventHandler, useEffect } from "react";

let instance: any = null;

export const HomeContainer = async () => {
  useEffect(() => {
    window.HEIC_DECODER().then((mod) => {
      instance = mod;
    });
  }, []);

  const onInput: FormEventHandler<HTMLInputElement> = async (img) => {
    const { _test, FS_createDataFile, ...t } = instance;
    console.log("t", t);
    const files = img.target.files || [];
    if (files.length == 0) return;
    var file = files[0];

    const fr = new FileReader();
    fr.onload = function () {
      FS_createDataFile("/", "test.heic", file, true, true, true);
    };
    fr.readAsArrayBuffer(file);
    console.log(`Square root of 16 is ${_test()}`);
  };

  const readFile = async () => {
    const { _read_file } = instance;
    console.log(
      "readFile",
      instance.ccall("read_file", "number", ["string"], ["test.heic"])
    );
  };

  return (
    <div>
      <input type="file" id="file" accept=".heic,.heif" onInput={onInput} />
      <Image id="img" height="100" width="100" src="" alt="" />
      <button onClick={readFile}>Read File</button>
    </div>
  );
};
