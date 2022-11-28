# sha1crawler

## Overview
**sha1crawler** is a simple [Qt](http://qt-project.org)-based example command-line tool for generating [SHA-1](http://en.wikipedia.org/wiki/SHA-1) hashes for files within a given directory structure.

It generates a single `sha1` file for **each** subdirectory, starting from a base target directory, that contains the name and hash of each file within that same directory.

### Installation
sha1crawler can be built using the [Qt SDK](http://qt-project.org/downloads).  A project file (Sha1Crawler.pro) is provided for convenience.

Once compiled, the program can be executed directly from the command-line (with suitable execute permissions) or placed within a location contained in your PATH environment variable.

### Usage
A single command-line argument to the base target directory is required to start the crawling process.

Basic usage example:  

	[host:~]% sha1crawler target_dir
	
A file named `sha1` will be created in the target directory (and in each subdirectory, including symlinked directories) if that same directory contains one or more files.

Each `sha1` file will contain the name and SHA-1 hash of each file within the same directory, separated by a colon.  For example, for a directory containing the files `file1`, `file2`, and `file3` the output contained in the `sha1` file might be:

	file1:60b27f004e454aca81b0480209cce5081ec52390
	file2:cb99b709a1978bd205ab9dfd4c5aaa1fc91c7523
	file3:1eb2267bae4e47cab81f8866bbc7e06764ea9be0

During the crawling process the program outputs several informative messages to indicate its progress:

		Sha1 crawler starting..
  			+ adding hash for /Users/fidget/basedir/file1
  			+ adding hash for /Users/fidget/basedir/file2
  			+ adding hash for /Users/fidget/basedir/file3
		Success.
		
If the files in the directory tree are changed at any time, you can re-run the program to update the `sha1` files (and update the SHA-1 hashes that they contain).  sha1crawler simply removes the old `sha1` file and generates a new one.  For example:

		Sha1 crawler starting..
 		 	- deleting sha1 from /Users/fidget/basedir
  			+ adding hash for /Users/fidget/basedir/file1
 		 	+ adding hash for /Users/fidget/basedir/file2
 		 	+ adding hash for /Users/fidget/basedir/file2
		Success.

### Cleanup
If you need to remove the `sha1` files from a directory tree, use the following command at the shell prompt, replacing _target_path_ with the base directory path from which to start the removal process:  

	find target_dir -name sha1 -exec rm {} \;

_Warning: this will permanently delete all files matching the -name parameter ('sha1' in the example above) from the target_dir directory and any subdirectories in which the file exists.  Use with care._

### License
sha1crawler is licensed under the [GNU General Public License v3.0](http://www.gnu.org/licenses/gpl.html).

## Contact
Email me at [marc.ransome@fidgetbox.co.uk](mailto:marc.ransome@fidgetbox.co.uk) or [create an issue](https://github.com/marcransome/sha1crawler/issues).

