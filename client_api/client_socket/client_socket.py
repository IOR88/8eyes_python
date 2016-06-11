from socket import socket, SOL_SOCKET, SO_REUSEADDR, SHUT_RDWR, SHUT_WR
from socket import error
from socket import AF_INET, SOCK_STREAM


class ClientSocket:
    def __init__(self, *args, **kwargs):
        self.HOST = kwargs.get('HOST', None)
        self.PORT = kwargs.get('PORT', None)
        self.FAMILY = kwargs.get('FAMILY', None)
        self.TYPE = kwargs.get('TYPE', None)
        self.socket = None

    def __create_socket__(self, server=None):
        """
        :arg server Bool()
        """
        self.socket = socket(family=self.FAMILY, type=self.TYPE)

    def __close_socket__(self):
        try:
            self.socket.shutdown(SHUT_WR)
        except (OSError,) as err:
            pass
        self.socket.close()


class ClientSocketAPI(ClientSocket):

    def __init__(self, *args, **kwargs):
        super(ClientSocketAPI, self).__init__(self, *args, **kwargs)
        self.__create_socket__()

    def connect(self):
        try:
            self.socket.connect((self.HOST, self.PORT))
        except (error,) as err:
            print(err)

    def disconnect(self):
        self.__close_socket__()


if __name__ == "__main__":
    client = ClientSocketAPI(HOST='localhost',
                             PORT=8003,
                             FAMILY=AF_INET,
                             TYPE=SOCK_STREAM)
    client.__create_socket__()
    client.connect()

    while True:
        data = client.socket.recv(1024)
        if data:
            print('DATA FROM DEMON', data)
        else:
            pass