const fs = require("fs");
const spawn = require("child_process").spawn;

fs.readFile("package.json", "utf8", function(err, data) {
  if (err) throw err;
  data = JSON.parse(data);

  data.version = `${data.version.split(".")[0]}.${
    data.version.split(".")[1]
  }.${parseInt(data.version.split(".")[2]) + 1}`;

  out_str = JSON.stringify(data, null, 2) + "\r";

  fs.writeFile("package.json", out_str, "utf8", err => {
    if (err) throw err;
    free = spawn("git", ["add", "package.json"]);
  });
});
