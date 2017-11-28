
import nanomsg

print(nanomsg)

s = nanomsg.nn_socket(nanomsg.AF_SP, nanomsg.NN_REP)
print("s", s)

endpoint = nanomsg.nn_bind(s, "tcp://127.0.0.1:22222")
print("endpoint", endpoint)

s2 = nanomsg.nn_socket(nanomsg.AF_SP, nanomsg.NN_REQ)
print("s2", s2)
endpoint = nanomsg.nn_connect(s2, "tcp://127.0.0.1:22222")
print("endpoint", endpoint)

nbytes = nanomsg.nn_send(s2, b"hello", 0)
print("nbytes", nbytes)
assert nbytes == 5

b = bytearray(b"........")
nbytes = nanomsg.nn_recv(s, b, 0)
print("nbytes", nbytes)
print(b)
print(b[:nbytes])

print("OK")
