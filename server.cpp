#include <jubatus/msgpack/rpc/server.h>
#include <jubatus/msgpack/rpc/client.h>

#include <vector>

class heavy_server : public msgpack::rpc::dispatcher {
 public:
  void dispatch(msgpack::rpc::request req) {
    std::string method;
    req.method().convert(&method);
    if (method == "train") {
      // train method is slow.
      ::sleep(15);
      req.result(1);
    } else {
      std::vector<std::vector<int> > result;
      req.result(result);
    }
  }

  msgpack::rpc::server& listen(const std::string& host, uint16_t port) {
    m_svr.serve(this);
    m_svr.listen(host, port);
    return m_svr;
  }

 public:
  heavy_server()
  : m_sp(m_svr.get_loop()) {}

 private:
  msgpack::rpc::server m_svr;
  msgpack::rpc::session_pool m_sp;
};

int main() {
  heavy_server s;
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) { exit(1); }
  s.listen("0.0.0.0", 12345).run(64);
}
