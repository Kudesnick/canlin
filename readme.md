# can/lin scanner

## commands

### Help

`help|h|?`

### start scanning and brake scanning

`run [ifaces list] [file path]`

Start scanning. Use Ctl+C to brake scanning for all runing interfaces. If set `file path`, then log writing to flash card.

### Show settings

`show [ifaces list]`

### Show tasks

`task [show|clr]`

Showed or cleared all messages in queue to send

## settings

### CAN settings

```
CAN (A|B|C) sett <baudrate>[type] [flags]
baudrate:
    %d [SJW %d] [S1 %d] [S2 %d]
type:
    fd [<data baudrate>] - use FD-CAN with special data baudrate.
flags:
    t - terminator on
    s - silent mode
```

### UART settings

```
LIN (A|B) sett <baudrate> [<sett>] [brk] [flags]
baudrate:
    (%d|auto|ab|as)
sett:
    <byte len><parity><stop bits> - (5..9)(N|E|O|M|S)(1|1.5|2) - data setting
brk:
    (10|11) brake frame length
```

## send msg

### common sending format

```
<iface> <type> <msg> [| <repeat interval> [<repeat counter>]]
iface:
    CAN (A|B|C) or LIN (A|B)
```
if used repeat but repeat counter not set, then message repeated infinity

### CAN msg format

```
type:
    (STD|EXT)
msg:
    <id> <hex data> - 0x7E0 00 12 45 f0
        or 0x1003 03E8561703E85617
```

### LIN msg format

```
type:
    (STD|EXT|RAW)
msg:
    [id %d] <hex data> [CS]
    id - if used this parameter, then thist byte will be corrected as LIN ID
    CS - flag - calculate checksum
```
