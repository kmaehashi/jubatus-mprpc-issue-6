all:
	g++ server.cpp -L/tmp/jubatus/lib -L/opt/jubatus/lib -ljubatus_msgpack-rpc -ljubatus_mpio -lmsgpack -o server
