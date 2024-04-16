// import module
import { ccall } from "./a.out.js";

const file = document.getElementById("file");
const img = document.getElementById("img");

file.addEventListener("change", (e) => {
  const file = e.target.files[0];
  const reader = new FileReader();

  reader.onload = (e) => {
    img.src = e.target.result;
    console.log("test", ccall());
  };

  reader.readAsDataURL(file);
});
