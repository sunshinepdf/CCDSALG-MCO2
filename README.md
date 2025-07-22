# CCDSALG-MCO2

<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a id="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/sunshinepdf/CCDSALG-MCO2">
  </a>

<h3 align="center">MCO2-CCDSALG: Social Network</h3>

  <p align="center">
    This project implements an undirected graph representation of relationships among members of a Social Networking Site (SNS). The project applies the implementation of BFS and DFS graph traversal algorithms. 
    <br />
    <br />
    This project was created by: Nathan Laborada, Ashley Fiona Lee, and Khyle Villorente in partial completion of their requirements for the course CCDSALG.
    <br />
    <a href="https://github.com/sunshinepdf/CCDSALG-MCO2">View Demo</a>
    <br />
    <a href="https://github.com/sunshinepdf/CCDSALG-MCO2">Check project specs</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installing-your-local-repo">Installing your local repo</a></li>
        <li><a href="#commit-and-request-protocols">Commit and Request Protocols</a></li>
      </ul>
    </li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

 This project takes a text file input containing information of the undirected graph and it's adjacency information. A variety of text file outputs are generated to represent the contentsof the processed undirected graph.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* [![C][C-shield]][C-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

To set up a local copy follow these simple steps.

### Prerequisites

Ensure you have atleast GCC v14.2.0 installed on your desktop. Run the prompt below in your terminal to check.
* gcc 
  ```sh
  gcc --version
  ```
The following (or something similar) should be displayed:
  ```sh
  gcc (GCC) 14.2.0 
  Copyright (C) 2024 Free Software Foundation, Inc.
  ```
Ensure you have Git installed. [Installer Link Here](https://git-scm.com/downloads/win)
<br />
Follow the installation guide on the website then run the prompt below in your terminal to check.
* git 
  ```sh
   git --version
  ```
### Installing your local repo

1. Clone the repo on your local desktop by inputting the prompt in your terminal.
   ```sh
   git clone https://github.com/sunshinepdf/CCDSALG-MCO2.git
   ```
   
2. Go into the file that git just created.
   ```sh
   cd MCO2-CCDSALG # edit if the directory you cloned the repo in is different
   ```
   
3. Change git remote url to avoid accidental pushes to base project
   ```sh
   git remote set-url origin https://github.com/sunshinepdf/CCDSALG-MCO2.git
   git remote -v # confirm the changes
   ```
   
### Commit and Request Protocols

1. To avoid merge conflicts always run:
   ```sh
   git branch # make sure that you are currently on main
   git pull
   git status # run to confirm that your branch is up to date
   ```
   before working on your code.
   <br />
   This ensures that the current data in your local repository, matches the data uploaded on our main repository.

3. Create a new branch for every added feature, edit, or resolved issue.
   ```sh
   git checkout -b <branch_name> # creates a new branch and switches you to that branch automatically
   ```
   Suggested format of the branch name:
       **##/type/branchName**
   
    * The **##** represent the feature number
      
    * The **type** represents that kind of changes made and should be changed to:
       + feature - if a new function is added,
       + edit - if minor edits (e.g. documentation, minor fixes, etc.) is added,
       + resolvedIssue - if a bug has been fixed.
         
    * The **branchName** represent the name of the edits to be merged with main
      <br />
      _Make sure the branchName is comprehensive and describes the changes made as concise as possible_

4. To switch branches run the commands below
   ```sh
   git branch # lists the existing branches
   git checkout <branch_name> # switches you to that branch
   ```
5. Once changes are done in the branch, you should add, commit, and push changes to the remote:
   ```sh
   git add .
   git commit -m "insert message"
   git push -u origin <branch name>
   ```
For further details on other git commands feel free to read the guide [here](https://www.atlassian.com/git/glossary#commands).
<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- ROADMAP -->
## Roadmap
_will be updated once a detailed timeline is set_
- [ ] Feature 1
- [ ] Feature 2
- [ ] Feature 3
    - [ ] Nested Feature

See the [open issues](https://github.com/sunshinepdf/CCDSALG-MCO2/issues) for a full list of planned features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Nathan Laborada - nathan_laborada@dlsu.edu.ph
<br />
Ashley Fiona Lee - ashley_lee@dlsu.edu.ph
<br />
Khyle Villorente - khyle_raeka_b_villorente@dlsu.edu.ph

Project Link: [https://github.com/sunshinepdf/CCDSALG-MCO2](https://github.com/sunshinepdf/CCDSALG-MCO2)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* []()
* []()
* []()

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/sunshinepdf/CCDSALG-MCO2.svg?style=for-the-badge
[contributors-url]: https://github.com/sunshinepdf/CCDSALG-MCO2/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/sunshinepdf/CCDSALG-MCO2.svg?style=for-the-badge
[forks-url]: https://github.com/sunshinepdf/CCDSALG-MCO2/network/members
[stars-shield]: https://img.shields.io/github/stars/sunshinepdf/CCDSALG-MCO2.svg?style=for-the-badge
[stars-url]: https://github.com/sunshinepdf/CCDSALG-MCO2/stargazers
[issues-shield]: https://img.shields.io/github/issues/sunshinepdf/CCDSALG-MCO2.svg?style=for-the-badge
[issues-url]: https://github.com/sunshinepdf/CCDSALG-MCO2/issues
[C-shield]: https://img.shields.io/badge/-C-blue.svg?style=for-the-badge&logo=c
[C-url]: https://devdocs.io/c/

