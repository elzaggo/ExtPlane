#
"""
"""
from twisted.internet.protocol import Protocol, ClientFactory
from twisted.protocols import basic

from twisted.internet import stdio
from twisted.internet import reactor

import os

#host ="192.168.30.30"
#port = 51000
host ="localhost"
port = 8000

net_pipe = None

class NetClient(Protocol):
    def __init__(self, console):
        self.console = console
        
    def sendLine(self, line):
        self.transport.write(line)
        
    def dataReceived(self, data):
        self.console.sendLine(data)
        self.console.sendPrompt()

class Console(basic.LineReceiver):
    from os import linesep as delimiter

    def connectionMade(self):
        pass

    def sendPrompt(self):
        self.transport.write('>>> ')

    def lineReceived(self, line):
        self.net_pipe.sendLine(line)
            

class ExtPlaneClientFactory(ClientFactory):
    def __init__(self, console):
        self.console = console

    def startedConnecting(self, connector):
        self.console.sendLine('Started to connect.')

    def buildProtocol(self, addr):
        self.console.sendLine('Connected.')
        self.console.sendPrompt()
        self.console.net_pipe = NetClient(self.console)
        return self.console.net_pipe

    def clientConnectionLost(self, connector, reason):
        print 'Lost connection.  Reason:', reason

    def clientConnectionFailed(self, connector, reason):
        print 'Connection failed. Reason:', reason

console = Console()
stdio.StandardIO(console)
reactor.connectTCP(host, port, ExtPlaneClientFactory(console))
reactor.run() 
