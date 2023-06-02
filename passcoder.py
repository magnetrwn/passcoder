"""
passcoder.py

Basic Text Encrypt/Decrypt Script Tool
(AES-CTR + PBKDF2 + zlib)

This is not a general-purpose tool, but only a straightforward script.
This module provides a basic tool for encrypting and decrypting text,
specifically designed to enhance the security of storing passwords on
paper media. It employs a multi-step encryption process.

Usage:
   python3 passcoder.py [encode/decode] [text] [password] [salt]
   Parameters can be skipped to enter Wizard Mode, see Usage Details.

Encryption Process (invert for decryption):
1. Encryption Key Generation:
   The plaintext password and salt fields are used as inputs to generate
   an encryption key. The key is derived from the hash returned by PBKDF2.

2. AES Cipher Initialization:
   The generated encryption key is utilized to initialize an AES cipher
   in Counter mode. Additionally, a randomly generated nonce is created.

3. zlib Text Compression
   Before encoding, the plaintext is compressed using zlib to reduce
   final string length.

4. Ciphertext Encoding:
   The plaintext is encrypted using the AES cipher in Counter mode.
   The resulting ciphertext is concatenated with the nonce to form
   the final encoded string.

To securely store passwords using this tool, it is essential to
safely store two values other than the ciphertext:
1. Password: A string representing the password itself.
2. Salt: A fromhex string used as a parameter for key derivation.

Usage Details:
1. Wizard Mode:
   The module provides an interactive wizard that prompts for each
   required value. It offers structured input options and, if desired,
   default values can be utilized.

2. Argument Mode:
   Values can be passed as arguments when executing the module.
   This allows for automation of the encryption and decryption process.
   If not ready, a subset of arguments can be added, and the rest will
   be prompted in Wizard Mode.

Sample Application:
   An interesting use of this script is also my reason for its creation:
   the writing of a password backup leaflet encrypted in a recoverable
   way. The decryption password can be kept the same across the booklet,
   while the salt can be hidden some other way.
"""

import codecs
import sys

from Crypto.Cipher import AES
from Crypto.Protocol.KDF import PBKDF2
from Crypto.Random import get_random_bytes

_DEF_DKLEN_SIZE = 16
_DEF_NONCE_SIZE = 8
_DEF_SALT_SIZE = 4


def safe_input(prompt, valid_inputs=None):
    """Prompt the user for a valid input in a nice way."""
    while True:
        try:
            print("\x1B[0m", end="")
            prompt += "\x1B[01;91m"
            got = input(prompt)
            if not got.isascii():
                raise UnicodeError
        except KeyboardInterrupt:
            print("\x1B[0m", end="")
            sys.exit("\n|   |_, Interrupted from keyboard.")
        except UnicodeError:
            print("\x1B[0m", end="")
            print("|   |_, Please only use ASCII.\n|")
        else:
            print("\x1B[0m", end="")
            if valid_inputs is not None:
                if got in valid_inputs:
                    break
                else:
                    print("|   |_, Invalid action.\n|")
            else:
                break
    return got


def encrypt_ascii(plaintext, password, salt):
    """Encrypt an ASCII string."""
    key = PBKDF2(password, salt, dkLen=_DEF_DKLEN_SIZE)
    nonce = get_random_bytes(_DEF_NONCE_SIZE)
    cipher = AES.new(key, AES.MODE_CTR, nonce=nonce)
    ciphertext = cipher.encrypt(codecs.encode(plaintext.encode("ascii"), "zlib"))
    return ciphertext + nonce


def decrypt_ascii(ciphertext, password, salt):
    """Decrypt to an ASCII string."""
    key = PBKDF2(password, salt, dkLen=_DEF_DKLEN_SIZE)
    nonce = ciphertext[-_DEF_NONCE_SIZE:]
    ciphertext = ciphertext[:-_DEF_NONCE_SIZE]
    cipher = AES.new(key, AES.MODE_CTR, nonce=nonce)
    plaintext = codecs.decode(cipher.decrypt(ciphertext), "zlib")
    return plaintext.decode("ascii")


if __name__ == "__main__":
    ACTION = None
    ACTIONTEXT = None
    PASSWORD = None
    SALT = None

    if len(sys.argv) > 5:
        sys.exit("Too many arguments.")

    print("\nBASIC ACTIONTEXT ENCRYPT/DECRYPT TOOL FOR PAPER SUPPORTS\n|")

    if len(sys.argv) >= 2:
        ACTION = sys.argv[1]
    if len(sys.argv) >= 3:
        ACTIONTEXT = sys.argv[2]
    if len(sys.argv) >= 4:
        PASSWORD = sys.argv[3]
    if len(sys.argv) == 5:
        SALT = sys.argv[4]

    if ACTION is None:
        ACTION = safe_input(
            "|_, Do you want to encode or [decode]?\n|   ", ["encode", "decode", ""]
        )
    if ACTION == "":
        ACTION = "decode"
    if ACTION not in ["encode", "decode"]:
        sys.exit("Unknown action mode.")

    if ACTIONTEXT is None:
        if ACTION == "encode":
            ACTIONTEXT = safe_input("|_, Type your plaintext (ASCII).\n|   ")
        else:
            ACTIONTEXT = bytes.fromhex(
                safe_input("|_, Type your ciphertext (fromhex).\n|   ")
            )
    if PASSWORD is None:
        PASSWORD = safe_input("|_, Type your password.\n|   ")
    if SALT is None:
        SALT = safe_input("|_, Type your salt (fromhex), or [random].\n|   ")
        if SALT in ["", "random"]:
            SALT = get_random_bytes(_DEF_SALT_SIZE)
        else:
            while True:
                try:
                    SALT = bytes.fromhex(SALT)
                    break
                except ValueError:
                    print("|   |_, Please use [0-9a-f] only.\n|")
                SALT = safe_input("|_, Type your salt (fromhex), or [random].\n|   ")

    if ACTION == "encode":
        print(
            "V\nCIPHERTEXT:\x1B[01;91m",
            encrypt_ascii(ACTIONTEXT, PASSWORD, SALT).hex(),
            "\x1B[0m",
        )
    else:
        print(
            "V\nPLAINTEXT:\x1B[01;91m",
            decrypt_ascii(ACTIONTEXT, PASSWORD, SALT),
            "\x1B[0m",
        )

    print("PASSWORD:\x1B[01;91m", PASSWORD, "\x1B[0m")
    print("SALT:\x1B[01;91m", SALT.hex(), "\x1B[0m")
