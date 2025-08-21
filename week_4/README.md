# Recover (CS50 Problem Set 4)

## Overview
This program implements a **JPEG recovery tool**.  
It extracts JPEG images from a raw forensic memory card file by scanning through the data in fixed-size blocks and reconstructing each image.

Steps:
1. Read the memory card file in **512-byte blocks**.  
2. Detect the start of a new JPEG using its **header signature**.  
3. If a new JPEG is found, close the current file (if any) and open a new one.  
4. Continue writing blocks until the next header is found.  
5. Save all recovered images sequentially as `000.jpg`, `001.jpg`, `002.jpg`, …  

---

## How It Works

1. **Input**
   - The program accepts a single command-line argument: the name of the raw memory card file (e.g., `card.raw`).

2. **Data Structures**
   - `uint8_t buffer[512]`: temporary storage for each block read.  
   - `FILE *image`: pointer to the currently open JPEG file (if any).  
   - `counter`: integer used to number recovered JPEGs (`000.jpg`, `001.jpg`, …).  

3. **Functions**
   - `fread()` → reads 512-byte blocks from the input file.  
   - `fwrite()` → writes blocks into the current JPEG file.  
   - `fopen()` / `fclose()` → handles opening and closing image files dynamically.  
   - `sprintf()` → formats filenames (`"%03i.jpg"`) for each recovered file.  

4. **JPEG Detection**
   - A block is identified as a JPEG header if its first bytes match:  
     ```
     0xff 0xd8 0xff 0xe0–0xef
     ```
     Verified with:  
     ```c
     buffer[0] == 0xff &&
     buffer[1] == 0xd8 &&
     buffer[2] == 0xff &&
     (buffer[3] & 0xf0) == 0xe0
     ```

---

## File Structure
- **recover.c** → full implementation  
- Functions used:  
  - `fread`, `fwrite`, `fopen`, `fclose`, `sprintf`  

---

## Example Run

```bash
$ ./recover card.raw
```
Output:

000.jpg
001.jpg
002.jpg
...
Each recovered file can be opened as a normal image.

---

## Notes
- Works **block-by-block** (`512` bytes) since FAT file systems use this sector size.
- Ensures no data is written until the first JPEG header is found (`if (counter > 0)`).
- Uses **sequential filenames** to avoid collisions.
- **Includes safe** `if (image != NULL)` check before closing files.

---

## Author
- **Name:** Jerome Henry
- **Date:** August 2025

---

## Recruiter Note
This project demonstrates my ability to:
- Work with **low-level file I/O** in C (`fopen`, `fread`, `fwrite`).
- Apply **bitwise operations** to detect file signatures.
- Manage **dynamic file creation** and **memory safety**.
- Build a **forensic tool** that reconstructs deleted or fragmented data.

It showcases skills in C programming, debugging, and systems-level problem solving — directly relevant to cybersecurity and system/network engineering.