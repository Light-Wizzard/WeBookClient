# WeBookClient is Pronounced Web-Book-Client

WeBookClient is a Client/Server based Web-Book Content Management System

This is WeBookClient, it is meant to work with WeBookServer.
The documentation is spread out between [WeBook](https://github.com/Light-Wizzard/WeBook) and
[WeBookServer](https://github.com/Light-Wizzard/WeBookServer).

You can find more information at the Wiki's [WeBook Wiki](https://github.com/Light-Wizzard/WeBook/wiki),
[WeBookClient Wiki](https://github.com/Light-Wizzard/WeBookClient/wiki), [WeBookServer Wiki](https://github.com/Light-Wizzard/WeBookServer/wiki).

I used the Qt Rich Text Editor Project and documentation.

## Table Of Content

* [Table Of Content](#Table-Of-Content)
* [Status](#Status)
* [Downloads](#Downloads)
* [Windows](#Windows)
* [Mac](#Mac)
* [Linux](#Linux)
* [Concept](#Concept)

## Status

Unix: Linux & Mac: [![Travis Build Status](https://travis-ci.com/Light-Wizzard/WeBookClient.svg?branch=master)](https://travis-ci.com/Light-Wizzard/WeBookClient)

Windows: [![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/l72fncva61fru2h4?svg=true)](https://ci.appveyor.com/project/Light-Wizzard/WeBookClient)

I am posting this only so I can get the Travis and AppVeyor Builds to work.

Currently it works somewhat, and missing a lot of features,
currently Chat talks with the WeBookServer.

## Downloads

Linux
- :penguin: [Linux](https://github.com/Light-Wizzard/WeBookClient/releases/download/continuous/WeBookClient-travis-x86_64.AppImage)
- :penguin: :inbox_tray: [Linux ZSync](https://github.com/Light-Wizzard/WeBookClient/releases/download/continuous/WeBookClient-travis-x86_64.AppImage.zsync)

Windows see [Windows](#Windows)
- :office: [Windows zip exe](https://github.com/Light-Wizzard/WeBookClient/releases/download/continuous/WeBookClient-release.zip)
- :office: :outbox_tray: [Windows Installer exe](https://github.com/Light-Wizzard/WeBookClient/releases/download/continuous/WeBookClient-Installer.exe)
- :office: :outbox_tray: [Windows Installer zip](https://github.com/Light-Wizzard/WeBookClient/releases/download/continuous/WeBookClient-Installer.zip)

Mac
- :apple: [Apple](https://github.com/Light-Wizzard/WeBookClient/releases/download/continuous/WeBookClient.dmg)

## Windows

I have tested the WeBookClient Installer and Uninstaller, both are working.

The App should work on Windows 7 or greater.

I test on Windows 10 Pro.

## Mac

I do not own a Mac, so I cannot test it.

## Linux

This app was written and tested on Arch Linux Manjaro, as well as Ubuntu LTS.

## Concept

The WeBook Concept is to have a Client known as WeBookClient,
communicate and control the Server known as WeBookServer,
in a multi-user collaboration, designed for managing Web-Books.

A Web-Book also known as a WeBook,
is an HTML Document that is edited using Qt C++ Rich Text Widget,
and saves it as an HTML Document, and when published with send it to the WeBookServer,
which can be running on your Local Machine, on a Machine in your Local Network,
or a Public VPS account, where every WeBook can be its own Website.

When completed, it will allow multiple users, the ability join your Domain,
or you can join others, the concept is to Fork this Project,
and make your own WeBook Domains,
the concept of Forking, is so you have your Own GitHub Repository,
you do not need to alter the Code,
its Designed to be Forked,
the End Users who Fork it,
only need to do pulls to keep it up to date.

This Project uses Zsync2, I am going to write a full Tutorial on how to use it,
basically it allows you to push updates to your Travis and AppVeyor builds,
and anyone that has this App installed, will get a notification of the Update,
and it self updates, so no need to make a Linux Repository,
since you only need to install the App, I use Qt Installation Framework,
so you have a nice Uninstaller also.

I am writing this for Individuals who want to write a book,
but want more control over it than Word or Writer can offer,
this is not to replace them, in fact it creates documents for them.

Why use WeBook instead of Word or Writer or other Word Processors?

WeBook creates Documents for all Word Processors, that is its only job,
so the question is, why use WeBook to make Documents.

The really of Word Processors is called Malware and Viruses,
WeBook only uses Rich Text HTML, to eliminate this threat,
currently if saves PDF and HTML,
I will expand this to ePub, Docx, RTF, Text, and others,
and all of them will be less likely to contain malicious code,
its really up to the User who inputs the code,
and by code, I am talking about the HTML code in the Document itself,
and there is not much you can do with HTML that is malicious,
and why its better to use WeBook than normal Word Processors.

I have a Windows 360 account, and for one reason, I want this app to interface with it,
and that is not a program, in fact, it will make it very easy to manage documents from One-drive,
as it is Google Drive, or others.

Currently I do not have an Import feature,
it will be added at some point,
first I have to have a Docx Engine,
and Doc, Open Office it does by default,
my goal is to be able to convert from any format.

This project is gear for Military or Government work,
that is where the majority of all the code I have write goes,
my goal is to write an Application that can Manage Technical Manuals,
that is what a WeBook is all about.

Security is a major goal, and this Client/Server is geared to be a Point-to-Point Security System,
but its Security is not part of this Application,
making it hard to attack, and no reason to hack it to try to use it to attack,
and I got into great deal about how the WeBook Security System Works,
and when completed, I will set up a Hack Server,
and invite the World to try to Hack in,
and just let it go, with no abnormal administration,
just normal usage, to prove it can sustain a DoS or Brute Force attacks,
without effecting Clients.

The Reason I wrote this Content Management System,
is to document the End of Times,
according to Sir Isaac Newton,
who Calculated this would happen in the year of 2060 under the Julian Calendar,
this can be confirmed by calculating when the Magnetosphere will be gone,
and that is in the year 2103, and Newton Calculated it would happen 42 years before that,
see https://github.com/Light-Wizzard/galaxy-calculator for more details.


## End of Read me.

You can stop reading now, or see the [Table Of Content](#Table-Of-Content)
