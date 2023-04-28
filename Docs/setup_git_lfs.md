# ---- Git LFS ----

## Initialization
$ git lfs install

## Resolve the issue [x509: certificate signed by unknown authority] while pushinng files
$ git config http.sslVerify false
$ git push -u origin main

Ref: https://blog.csdn.net/yana_balabala/article/details/113576775
