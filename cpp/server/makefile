u_server: udp_server
u_server.out: udp_server.cpp
	clang++ -c udp_server.cpp -o udp_server.out

s_client: s_client
s_client.out: s_client.cpp
	clang++ -c s_client.cpp -o s_client.out

s_server: s_server
s_server.out: s_server.cpp
	clang++ -c s_server.cpp -o s_server.out

.PHONY: clean
clean:
	-rm -rf *.out

#  .PHONY意思表示clean是一个“伪目标”
#  也即是无论clean是否最新，一定执行它
#  rm命令前面加了一个小减号的意思就是，也许某些文件出现问题，但并不理睬
#  clean的规则不要放在文件的开头，否则这就会变成make的默认目标

# 参考链接 https://www.cnblogs.com/tp-16b/p/8955462.html