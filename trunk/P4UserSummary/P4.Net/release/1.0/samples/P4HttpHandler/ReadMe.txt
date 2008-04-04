P4.Net HTTP Handler Sample

The HTTP Handler sample application is and HTTP handler for IIS that will
stream content through IIS directly from Perforce.  Althought p4web will
also do this, the HTTPHandler sample is unique in that the url is translated
from the right-hand side of the client view.  This allows the web presense to be 
manipulate in a number of ways to limit the visibility and paths that are exposed.

The default configuration will point the handler to the Perforce public depot
and the client spec will limit the view to only see the P4.Net documentation at 
the root of the web application.

Installation/configuration:
The web.config file is setup for IIS 7.0 (Vista/Longhorn).  Under Vista,
you simply need to compile the handler, deploy it with p4dn.dll and p4api.dll in a 
bin folder, and create a virtual directory or web site in IIS.  All other config should
work out-of-the-box.

For IIS 6.0, you will need to map all files to the ASP.Net ISAPI filter.  And you will need 
to modify the web.config to use IIS 6.0 specific syntax for registering HTTPHandlers.