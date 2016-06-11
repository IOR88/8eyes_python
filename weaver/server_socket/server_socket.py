from socket import socket, SOL_SOCKET, SO_REUSEADDR, SHUT_WR, AF_UNIX, SOCK_STREAM
import os
import sys


class WeaverSocket:

    def __init__(self, *args, **kwargs):
        self.FAMILY = kwargs.get('FAMILY', AF_UNIX)
        self.TYPE = kwargs.get('TYPE', SOCK_STREAM)
        self.CONNECTIONS = kwargs.get('CONNECTIONS', 1)
        self.SOCKET_FILE = kwargs.get('SOCKET_FILE', '/tmp/WeaverSocket.socket')
        self.socket = None
        try:
            self.remove_sock_file()
        except (Exception,) as err:
            pass
        self.__create_socket__()
        self.__bind_socket__()

    def __create_socket__(self):
        """
        :arg server Bool()
        """
        try:
            self.socket = socket(family=self.FAMILY, type=self.TYPE)
            # self.socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
        except (Exception,) as err:
            print("Exception during socket creation: ", err, "\n")
            sys.exit(1)

    def __bind_socket__(self):
        try:
            self.socket.bind(self.SOCKET_FILE)
        except (Exception,) as err:
            print("Exception during socket binding: ", err, "\n")
            sys.exit(1)

    # =========PUBLIC AP==========I #
    def close_socket(self):
        try:
            self.socket.shutdown(SHUT_WR)
        except (OSError,) as err:
            pass
        finally:
            self.socket.close()
            self.remove_sock_file()

    def remove_sock_file(self):
        os.remove(self.SOCKET_FILE)

    def run(self):
        """
        Override this one to provide needed connection handling
        :return:
        """
        self.socket.listen(self.CONNECTIONS)
        while True:
            conn, addr = self.socket.accept()

            print('accepted connection')

            while True:

                data = conn.recv(1024)
                if not data:
                    break
                else:
                    print("-" * 20)
                    msg = data.decode('utf-8')
                    print(msg)

if __name__ == "__main__":
    server = WeaverSocket()
    server.run()