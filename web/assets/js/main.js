import module from "../../../build/web/build.js";

const canvas = document.createElement("canvas");
canvas.id = "output";

document.body.appendChild(canvas);

module({canvas});