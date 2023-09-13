# Weaver
Weaver is a word transformation game developed in C.

The program is meant to provide an interactive way for users to move from a starting word to a target word, changing one letter at a time and ensuring every intermediary step is a valid dictionary word. I utilized linked lists to manage the database of words, pulling from a words.txt file. This design choice ensures memory efficiency and allows easy adaptability for a varying word database. For added complexity and flexibility, players can either choose the word length for their game or go with a random challenge where the system selects the words. To ensure smooth gameplay, I incorporated functions for validity checks, providing feedback to users when inputs deviate from game rules. This game is an exercise in efficient data structure use and user interface considerations.

## Installation and Usage

### Prerequisites
Ensure you have a C compiler installed, such as `gcc`.

### Steps:

1. **Clone The Repository**: 
   ```bash
   git clone <repository-url>
   cd path-to-repository/Weaver
2. **Compile The C File**:
   gcc -o weaver main.c
3. **Run The Program**:
   ./weaver
   
---
Thank you for taking the time to explore my project. Any feedback or contributions are always welcome
