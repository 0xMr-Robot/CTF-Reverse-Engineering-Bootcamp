## CTF Reverse Engineering Bootcamp

Instructor: Eslam Mohamed Abbas (Mr Robot)

Malware Analyst • Reverse Engineer • SOC Specialist • Instructor

- LinkedIn: www.linkedin.com/in/eslam-abbas-20aa64213
- Medium: https://medium.com/@0xMr_Robot
- Blog: https://0xmr-robot.github.io/
- GitBook: https://mr-robot-1.gitbook.io/mrrobot
- YouTube Channel: https://www.youtube.com/@BlacKSilence12
- Malware Analysis Fundamentals Playlist: https://www.youtube.com/playlist?list=PLgKWvRMsdLZ4N_okwVWqB6cgqeVQtZNC4

---

### Overview
This bootcamp is a fast‑paced, hands‑on introduction to reverse engineering specifically tailored for Capture The Flag (CTF) competitions. Across eight sessions, you will progress from fundamentals to practical exploitation of real CTF binaries, learning static/dynamic analysis, assembly, debugging, unpacking, and defeating anti‑analysis.

Recommended pre‑watch for the best experience: Malware Analysis Fundamentals playlist (see link above).

---

### Who Is This For?
- Beginners to intermediate participants who want a practical path into reverse engineering for CTFs
- Developers, SOC analysts, malware enthusiasts, and security researchers

### Prerequisites
- Basic programming familiarity (C/C++ or Python helps)
- Comfort with command line (Windows and/or Linux)
- A machine capable of running analysis tools and VMs

### Suggested Environment Setup
- Host OS: Windows 10/11 or Linux; optionally a Linux VM (Ubuntu/Kali)
- Analysis VM(s): Windows 10 and/or Ubuntu
- Core tools: IDA Free/Pro, Ghidra, Radare2/Cutter, x64dbg, OllyDbg, GDB, pwndbg/gef, UPX, Detect It Easy (DiE), PE-bear, strings/grep, CyberChef, Python 3 with capstone/unicorn/pycryptodome

---

## Curriculum

### Session 1: Introduction to Reverse Engineering for CTFs
- Topics:
  - Overview of reverse engineering and its role in CTFs
  - Introduction to key tools (IDA Pro, Ghidra, Radare2)
  - Setting up a CTF‑ready reverse engineering environment
- Goal: Gain a foundational understanding of reverse engineering in the context of CTFs
- Practice: Analyze a simple CTF binary to extract a flag

### Session 2: Assembly Language Basics
- Topics:
  - x86 assembly essentials (instructions, registers, memory)
  - Understanding control flow (loops, conditionals)
  - Disassembling simple CTF binaries
- Goal: Learn to read and interpret assembly code commonly found in CTF challenges
- Practice: Solve a crackme that requires understanding basic assembly instructions

### Session 3: Debugging Techniques for CTFs
- Topics:
  - Using debuggers (OllyDbg, x64dbg, GDB) for CTF tasks
  - Setting breakpoints and analyzing runtime behavior
  - Extracting flags by controlling execution flow
- Goal: Master dynamic analysis techniques for CTF problem‑solving
- Practice: Debug a CTF challenge to bypass a key check or extract hidden data

### Session 4: Binary Analysis for CTFs
- Topics:
  - Static and dynamic analysis tailored to CTF challenges
  - Identifying key functions, strings, and logic in binaries
  - Practical CTF examples of binary analysis
- Goal: Develop skills to statically analyze binaries and uncover CTF solutions
- Practice: Analyze a binary from a past CTF to find the flag without execution

### Session 5: Common Encryption Algorithms in CTFs
- Topics:
  - Cryptography basics (symmetric vs. asymmetric, block vs. stream ciphers)
  - Algorithms commonly seen in CTFs: XOR, RC4, AES, DES, ChaCha, RSA
  - Identifying encryption algorithms in binaries
- Goal: Understand and break common encryption schemes used in CTF challenges
- Practice: Decrypt data in a CTF challenge using the identified algorithm(s) (e.g., XOR, RC4)

### Session 6: Anti‑Analysis and Anti‑Reversing Techniques
- Topics:
  - Why anti‑analysis techniques are used in malware and CTFs
  - Obfuscation techniques: code, control‑flow, and data obfuscation
  - Other techniques: API hooking, VM detection, self‑modifying code
- Goal: Recognize and bypass common anti‑analysis techniques in CTF binaries
- Practice: Analyze an obfuscated CTF binary and deobfuscate key parts to find the flag

### Session 7: Anti‑Debugging Techniques and Packing
- Topics:
  - Introduction to anti‑debugging and its purpose
  - Common techniques: debugger detection (IsDebuggerPresent), timing checks, hardware breakpoints, exception tricks
  - Packing: what packers are, identifying common packers (e.g., UPX), unpacking techniques
- Goal: Learn to bypass anti‑debugging measures and unpack binaries in CTF challenges
- Practice: Bypass anti‑debugging in a CTF binary and unpack a packed executable (e.g., UPX‑packed)

### Session 8: CTF Practice and Crackmes
- Topics:
  - Full hands‑on session with real CTF challenges and crackmes
  - Applying techniques from all prior sessions (debugging, crypto, deobfuscation, unpacking)
  - Tips for effective CTF participation (time management, note‑taking, teamwork)
- Goal: Reinforce skills through practical application in a CTF‑style environment
- Practice: Solve a curated series of reverse engineering CTF challenges and crackmes

---

## Learning Outcomes
By the end, you will be able to:
- Systematically analyze CTF binaries using static and dynamic techniques
- Read and reason about x86 assembly and control flow
- Use debuggers effectively to alter execution and extract secrets/flags
- Identify and break common crypto usages in CTF contexts
- Recognize and defeat common anti‑analysis and anti‑debugging tricks
- Unpack and restore packed binaries for further analysis

---

## Resources and Further Learning
- Medium articles and write‑ups: https://medium.com/@0xMr_Robot
- Blog (posts, tools, updates): https://0xmr-robot.github.io/
- GitBook (structured notes and book summaries): https://mr-robot-1.gitbook.io/mrrobot
- Malware Analysis Fundamentals playlist (recommended pre‑watch): https://www.youtube.com/playlist?list=PLgKWvRMsdLZ4N_okwVWqB6cgqeVQtZNC4
- YouTube channel (reverse engineering and cybersecurity content): https://www.youtube.com/@BlacKSilence12

---

## Contact
For collaborations, training, or questions:
- LinkedIn: www.linkedin.com/in/eslam-abbas-20aa64213

Stay curious. Reverse everything. Capture the flag.
