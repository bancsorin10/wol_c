

# Wake on lan C implementation

Send magic packages to a computer that supports WOL in order to start it.

Magic packages are 6 bytes of `0xff` followed by 16 copies of the mac address
of the interface you are sending the magic pakages to.

# Usage

Change the mac address and the ip of the machine inside the `main.c`, then
compile and run the code

```
gcc main.c && ./a.out
```
