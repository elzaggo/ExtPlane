#
"""
"""
from twisted.internet.protocol import Protocol, ClientFactory
from twisted.protocols import basic

from twisted.internet import stdio
from twisted.internet import reactor


class NetClient(Protocol):
    def __init__(self, console):
        self.console = console
        
    def sendLine(self, line):
        if not line.endswith('\n'):
            line += '\n'
        self.transport.write(line)
        
    def dataReceived(self, data):
        self.console.sendLine(data)
        self.console.sendPrompt()


class CmdProcessor(object):
    def __init__(self):
        self.refs = {}

    def help(self):
        return """
        sub hg sim/cockpit2/gauges/actuators/barometer_setting_in_hg_pilot 1
        set hg 29
        inc hg -2
        \n"""

    def parse(self, line):
        parts = line.split()
        cmd, args = parts[0], parts[1:]
        if cmd is 'help':
            raise ValueError()
        elif cmd == 'sub' and len(args) == 3:
            self.refs[args[0]] = args[1:]
            return ['sub {} {}'.format(args[1], args[2])]
        elif cmd  == 'set' and len(args) == 2:
            ref, value = (self.refs[args[0]])[0], args[1]
            return ['set {} {}'.format(ref, value)]
        elif cmd  == 'inc' and len(args) == 2:
            ref, value = (self.refs[args[0]])[0], args[1]
            return ['inc {} {}'.format(ref, value)]
        else:
            raise ValueError()

        
class Console(basic.LineReceiver):
    from os import linesep as delimiter

    def __init__(self, cmd_processor):
        self.cmd_processor = cmd_processor

    def connectionMade(self):
        pass

    def sendPrompt(self):
        self.transport.write('>>> ')

    def lineReceived(self, line):
        try:
            lines = self.cmd_processor.parse(line)
            for l in lines:
                print 'sending line: ', l
                self.net_pipe.sendLine(l)
        except ValueError as e:
            self.transport.write(self.cmd_processor.help())
            self.sendPrompt()
            
            

class ExtPlaneClientFactory(ClientFactory):
    def __init__(self, console):
        self.console = console

    def startedConnecting(self, connector):
        self.console.sendLine('Started to connect.')

    def buildProtocol(self, addr):
        self.console.sendLine('Connected.')
        self.console.net_pipe = NetClient(self.console)
        return self.console.net_pipe

    def clientConnectionLost(self, connector, reason):
        print 'Lost connection.  Reason:', reason

    def clientConnectionFailed(self, connector, reason):
        print 'Connection failed. Reason:', reason


def main():
    import sys
    host = sys.argv[1]
    port = int(sys.argv[2])
    console = Console(CmdProcessor())
    stdio.StandardIO(console)
    reactor.connectTCP(host, port, ExtPlaneClientFactory(console))
    reactor.run()

#host ="192.168.30.30"
#port = 51000
#host ="localhost"
#port = 8000
    
main()
