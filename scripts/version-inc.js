const fs = require("fs");
const spawn = require("child_process").spawn;

fs.readFile("package.json", "utf8", function(err, data) {
  if (err) throw err;
  data = JSON.parse(data);

  version_list = data.version.split(".");
  reversion = parseInt(version_list[version_list.length - 1]);
  version_list[version_list.length - 1] = (reversion + 1).toString();
  version = version_list.join(".");

  data.version = version;

  out_str = JSON.stringify(data, null, 2) + "\n";

  fs.writeFile("package.json", out_str, "utf8", err => {
    if (err) throw err;
    free = spawn("git", ["add", "package.json"]);
  });
});
