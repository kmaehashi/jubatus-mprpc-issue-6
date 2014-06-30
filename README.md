train だけ 15 秒遅延し、classify は高速に応答するスタブclassifierサーバを立てる
---------------------------------------------------------------------------

```
$ cd heavy_server
$ make
$ ./server &  # localhost:12345 で動作
```

ZK上にスタブclassifier用のノードを作る
---------------------------------------------------------------------------

```
$ ./zkCli.sh
> create /jubatus/actors/classifier/sleeping ""
> create /jubatus/actors/classifier/sleeping/actives ""
> create /jubatus/actors/classifier/sleeping/actives/127.0.0.1_12345 ""
```

classifier プロキシを立ち上げる
---------------------------------------------------------------------------

```
$ jubaclassifier_proxy --rpc-port 9199 --interconnect_timeout 3 --pool_size 1 --pool_expire 60 &
```

セッションプールの中のコネクションをタイムアウトさせる
---------------------------------------------------------------------------

```
$ ./client-train.py
```

3秒後にタイムアウトが起きる (セッションプール内のセッションがタイムアウト状態となる)。
次の操作を 60 秒 (pool_expire) 以内に行う。

高速にレスポンスが返ってくるはずの処理を行う
---------------------------------------------------------------------------

```
$ ./client-classify.py
```

60 秒間待たされるはず、だったのだが…待たされない

