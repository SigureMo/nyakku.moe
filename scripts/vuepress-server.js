// based on
// https://blog.csdn.net/github_39457740/article/details/88780914

const http = require("http");
const fs = require("fs");
const url = require("url");
const path = require("path");
const docs = process.argv[2];
const docsDir = path.resolve(process.cwd(), docs);
const config = require(`${docsDir}/.vuepress/config.js`);
const { dest = ".vuepress/dist", base = "/" } = config;
const root = path.join(docsDir, dest);
const port = 8090;

let server = http.createServer(function(request, response) {
  let pathname = url.parse(request.url, true).pathname.replace(base, "/");
  let filePath = path.join(root, pathname);
  if (pathname == "/") {
    filePath = path.join(filePath, "/index.html");
  }
  console.log(pathname);
  console.log(filePath);

  fs.readFile(filePath, function(err, data) {
    if (err) {
      console.log(err);
      let errPath = path.join(root, "/404.html");
      fs.readFile(errPath, (err, data404) => {
        if (err) {
          response.write("404 Not Found");
          response.end();
        } else {
          response.writeHead(404, {
            "Content-Type": "text/html;charset='utf-8'"
          });
          response.write(data404);
          response.end();
        }
      });
    } else {
      response.write(data);
      response.end();
    }
  });
});
server.listen(port);
console.log(
  `> VuePress test server listening at http://localhost:${port}${base}`
);
