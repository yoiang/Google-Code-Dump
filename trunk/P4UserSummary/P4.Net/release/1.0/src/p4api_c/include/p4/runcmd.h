/*
 * Copyright 1995, 2003 Perforce Software.  All rights reserved.
 *
 * This file is part of Perforce - the FAST SCM System.
 */

/*
 * RunCommand() -- Just run a command and capture its output
 *
 * Classes:
 *
 *	RunCommand - run a command
 *
 *	RunArgs - a StrBuf for quoting command arugments to protect them
 *		   from the shell.  Note that is kind of a shambles right
 *		   now, in that RunChild() without the RCO_AS_SHELL command
 *		   calls execvp() on UNIX and so it breaks the command 
 *		   apart at spaces, ignoring quotes.
 *
 * Except where notes, these are implemented for UNIX, NT, VMS, MAC,
 * MACOSX, and OS2.
 *
 * Public methods:
 *
 *	RunArgs::AddArg() - add a single argument, quoting as needed
 *
 *	RunArgs::AddCmd() - add the first argument, which may be both
 *			a command and flags.  On Windows, we try to
 *			distinguish a command with spaces in it from
 *			a command followed by flags.  We do so by looking
 *			for the - or / introducing flags.
 *
 *	RunArgs::SetArgs() - clear the command buffer and add args
 *
 *	RunCommand::Run() - run the command
 *			Used by the client for launching editor, diff.
 *
 *	RunCommand::RunOut() - run the command, sending stdin, capturing stdout
 *			Used to run triggers for 'p4 submit'.
 *			Not implemented for MAC, VMS.
 *
 *	RunCommand::RunInWindow() - create a window to run the command
 *			Used by p4web for launching editor, resolve.
 *			Not implemented for MAC, VMS.
 *
 *	RunCommand::RunChild() - launch a subprocess whose stdin/stdout
 *			are the given fds.  
 *
 *	RunCommand::WaitChild() - wait for the child launched by RunChild().
 */

enum RunCommandOpts {

	RCO_SOLO_FD = 0x01,	// RunChild() uses same fd for I/O
	RCO_AS_SHELL = 0x02,	// RunChild() uses separate pipes, no socketPair

} ;

class RunArgs {

    public:

		RunArgs() {}
		RunArgs( const StrPtr &cmd ) { buf = cmd; }

	void	AddArg( const StrPtr &arg );
	void	AddArg( const char *arg );
	void	SetArgs( int argc, const char **argv );
	void 	AddCmd( const char *arg );

	StrBuf &SetBuf() { buf.Clear(); return buf; }

	RunArgs &operator <<( const char *a ) { AddArg( a ); return *this; }
	RunArgs &operator <<( const StrPtr &a ) { AddArg( a ); return *this; }

	char *	Text() { return buf.Text(); }

    friend class RunCommand;

    private:

	int	Argc( char **argv, int nargv );

	StrBuf	buf;

} ;

class RunCommand {

    public:
		RunCommand();
		~RunCommand();

	int 	Run( RunArgs &cmd, Error *e );
	int 	RunInWindow( RunArgs &cmd, Error *e );
	int 	RunOut( RunArgs &cmd, const StrPtr &in, StrBuf &out, Error *e );
	void 	RunChild( RunArgs &cmd, int opts, int f[2], Error *e );

	int 	RunOut( RunArgs &cmd, StrBuf &result, Error *e )
		{ return RunOut( cmd, StrRef::Null(), result, e ); }

	int	WaitChild();

    private:

# ifdef HAVE_FORK
	pid_t	pid;
# endif

# ifdef OS_NT
	void	*pid;
# endif

} ;

