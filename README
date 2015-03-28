# This is a scratch pad
### This repo is a brainstorming space for how a Ti.Next / Ti.Forward app might look when NOT running with a --legacy flag

The first and formost thought here is that we want something that can work with past Ti apps. But this should be an option and not the default.
This repo is about how a project might be laid out, just to see what makes sense.

Notable items
- tiapp.xml has a new scripts tag, the CLI would support a run param that you could select (think npm's script options `npm run scriptName`). Very useful for testing tools.
- No more Ti "build" directory. Ti init builds native projects (in the iOS, Android... directories) that get used. But we offload a lot more to those projects vs a proprietary Ti way of doing things... proprietary might save a little dev effort, but make things harder to debug, more brittle, and creates the need for a lot more documentation.
- Due to the above, no more need for copying things like info.plist from the build dir to the project root... just edit it in the platforms directory
- tiapp.xml under modules, now supports dynamic module platform types. npm will be an option out of the gate, but a plugin hook will be supported for other tools
- A lot of platform stuff was removed from tiapp.xml. Because we no longer completely rebuild the platforms native projects, this was no longer needed, again do it the native way.
- tiapp.xml also has a new tag for layoutEngine. Allowing for swappable engines if you like what ti has now, or someone wants something else.

Again, this is just brainstorming... think of something you want to add or dislike something here? It's open mic time!
