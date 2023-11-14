# GTK Passcoder

![passcoder Demo](demo.gif)

**Here is an overview of why this project might be of use to you, and why it even exists**

**Note:** Also feel free to make suggestions, raise issues and send PRs!

## What is this project about?

This project started when I wanted to have a local tool for password encryption.

While I could have used Python and could have had a way easier time using available libraries, I decided I'd rather make things from scratch to learn how they work.

This is why, looking through, working with, or improving the project, you will learn what this project tries to implement with [commonly available libraries](#what-do-i-need).

## What do I need?

You need to be intermediate-level in C++14 to understand this project. You will come across:
+ Widespread use of STL functionality, including algorithms and idioms,
+ Lambda functions,
+ Templated functions

You also need to understand how projects are divided into directories, headers and sources, ideally being aware of linkage properties and object/definition visibility and scope.

For things you need for building, see [How do I build](#how-do-i-build).

## What libraries do I need?

Some popular libraries used by the project are:
+ `Boost.JSON` for reading, parsing and writing JSON,
+ `GTKmm`, a GTK wrapper API for C++,
+ `OpenSSL`, a very popular cryptographic library and tool

## How does the project work?

It is essential to be aware of two things:
+ This project is designed for Linux use, specifically with a window manager that supports `GTK+3`,
+ The project is not yet fully completed, although the missing functionality is minimal (strings bulk load/save, clean all fields button, hide button and clipboard function).

Because of this, Windows developers may want to look elsewhere, I don't think this will easily be portable to Windows platforms.

Regarding the GUI, its design is entirely external and designed using `Glade`, a very nice application for laying out widgets similar to Qt Creator.

## How do I build?

You need at least CMake 3.12.0 to build the project, as well as its dependencies.

You will also need the previously mentioned libraries.

For Debian-based systems:
```bash
sudo apt-get install libgtkmm-3.0-dev libboost-all-dev libssl-dev cmake
```

