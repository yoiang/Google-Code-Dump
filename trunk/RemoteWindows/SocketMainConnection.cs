using System;
using System.Collections.Generic;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace RemoteWindows
{
    public class SocketMainConnection : Socket
    {
        public SocketMainConnection() : base( AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp )
        {
        }

        public void Enable( int Port, int MaxConnections)
        {
            IPAddress HostIp = (Dns.Resolve(IPAddress.Any.ToString())).AddressList[0];
            IPEndPoint HostEndPoint = new IPEndPoint(HostIp, Port);

            Bind(HostEndPoint);
            Listen(MaxConnections);
        }

        public void Disable()
        {
            Close();
        }
    }
}
