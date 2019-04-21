const fs = require("fs");
const path = require("path");
const spawn = require("child_process").spawn;

const tmp_dir = "tmp";
let options = process.argv;
let compiler;
let includes = [];
let compiled = [];
let out = "tmp\\tmp";

function get_includes(filepath) {
  let base = path.dirname(filepath);
  let code = fs.readFileSync(filepath, "utf8");
  let regExp = /# *?include *?\"(.+?)\"/g;
  let res;
  while ((res = regExp.exec(code))) {
    include_path = path.join(base, res[1]);
    if (!(include_path in includes)) {
      includes.push(include_path);
      get_includes(include_path);
    }
  }
  includes = Array.from(new Set(includes));
}

function gcc_c(filepath) {
  let extname = path.extname(filepath);
  let output = path.join(
    tmp_dir,
    path.basename(filepath).replace(extname, ".o")
  );
  compiled.push(output);
  spawn(compiler, ["-c", filepath, "-o", output]);
}

function gcc(compiled) {
  let args = ["-o", out];
  for (let compiled_item of compiled) {
    args.push(compiled_item);
  }
  spawn(compiler, args);
}

let main_c = options[2];
compiler = path.extname(main_c) == ".c" ? "gcc" : "g++";
get_includes(main_c);
gcc_c(main_c);
for (let include_path of includes) {
  gcc_c(include_path.replace(".h", ".c"));
}
gcc(compiled);
