"use strict";
var urls = [];
var date = "2018-10-11";
var datas = $.get("http://202.118.65.2/app/portals/recruiterNews?date=" + date);
for (let data of datas.responseJSON) {
  //要异步
  urls.push("http://202.118.65.2/app/portals/newspage.html?id=" + data.id);
}
function getmsg(url) {
  let html = "";
  msg = [];
  page = $.get(url);
  html = page.responseText; //要异步
  msg.push(html);
  return msg;
}
