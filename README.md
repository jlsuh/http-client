# http-client
```bash
$ make start ARGS="httpbin.org 80 /anything"
{
  "args": {},
  "data": "",
  "files": {},
  "form": {},
  "headers": {
    ...
  }, 
  "json": null,
  "method": "GET",
  "origin": ":)",
  "url": ...
}
```
```bash
$ make start ARGS="www.google.com 80 /"
HTTP/1.0 200 OK
Date: ...
Expires: -1
Cache-Control: private, max-age=0
Content-Type: text/html; charset=ISO-8859-1
P3P: CP="This is not a P3P policy! See g.co/p3phelp for more info."
Server: gws
X-XSS-Protection: 0
X-Frame-Options: SAMEORIGIN
Set-Cookie: ...; expires=...; path=/; domain=.google.com; Secure
Set-Cookie: ...; expires=...; path=/; domain=.google.com; HttpOnly
Accept-Ranges: none
Vary: Accept-Encoding
...
```
