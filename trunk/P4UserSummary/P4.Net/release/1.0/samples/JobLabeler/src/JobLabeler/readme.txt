JobLabeler Sample Application

*Setup
JobLabeler requires some administrative setup to work.  JobLabeler uses the 
'logger' command.  First, find out it logging is already enabled:
p4 counters

If you see a counter 'logger', it means another process is using the logger.  This 
process may clear the log... and if it does it will interfere with JobLabeler.
Identify the process(es) using logger, and see if they are running a logger command 
with both the -c and -t flags, it will clear the log.

If there is no counter named 'logger', you need to enable logging:
p4 counter logger 0

The Perforce user running JobLabeler needs a minimum of review access.

Look at the service's config file, and update any values.

JobLabeler uses a counter to maintain state of the last log entry read.
It turns out that you don't need to create this counter before running the service,
however you do need to ensure that the name of the counter (defined in the config
file) is unique.

JobLabeler can use a label as a template.  If you use this feature, make sure the 
template label exists before running the service.

To install the service, use the command-line utility sc.exe.  It's a standard utility
on Server 2003, or part of the resource kit for Widows 2000.  CD to the path of
the service:
sc create JobLabeler binPath= JobLabeler.exe DisplayName= "Perforce Job Labeler Service"

*Notes
JobLabeler currently will not catch up on existing fixes.  It will only process fixes
that occur after logger is enabled.  Catching up is a fairly straight-forward
modification to the JobLabeler sample, and is a good exercise for the user.