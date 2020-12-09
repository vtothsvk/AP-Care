# Git supply chain management

## Content

1. [Git BASH](https://github.com/vtothsvk/AP-Home/blob/main/Documentation/GIT.md#git-bash)
2. [Handling a git repo](https://github.com/vtothsvk/AP-Home/blob/main/Documentation/GIT.md#handling-a-git-repo)
3. [Git visual GUI](https://github.com/vtothsvk/AP-Home/blob/main/Documentation/GIT.md#git-visual-gui-gitkraken)
4. [Git repo workflow](https://github.com/vtothsvk/AP-Home/blob/main/Documentation/GIT.md#git-repo-workflow)
5. [Git Issues](https://github.com/vtothsvk/AP-Home/blob/main/Documentation/GIT.md#Git-Issues)
6. [Git project management](https://github.com/vtothsvk/AP-Home/blob/main/Documentation/GIT.md#Git-project-management)
7. [Formatting text - Markdown](https://github.com/vtothsvk/AP-Home/blob/main/Documentation/GIT.md#formatting-text---markdown)

## Git BASH

For convenient and fast code update and sharing using the Git supply chain manager GUI **Git BASH** is recommended.

* https://git-scm.com/download/win (Windows)
* https://git-scm.com/download/linux (Linux)

## Handling a git repo

### Cloning a repo

Git GUI is handled via cmd in Windows and via a terminal in Linux.

**1.** Create a directory for the project and navigate to your new directory

In Windows cmd:

```
C:Users\[yourUsername]> md MySuperDuperProject

C:Users\[yourUsername]> cd MySuperDuperProject

C:Users\[yourUsername]\MySuperDuperProject>
```

**2.** Clone the git repo

By **cloning** a git repository u locally cache its content to your machine creating a local repository that **tracks** the remote repository u cloned it from.
This allows you to make changes locally and then **push** them online to the remote repo or **pull** any changes from the remote repo to your local one using a single command instead of downloading unziping, copy-pasting and eventually getting lost :D .

Cloning is done by the git clone command:

```
*inside the folder u wanna clone the repo to
git clone [yourRemoteRepoLink]
```

eg.

```
C:Users\[yourUsername]\MySuperDuperProject> git clone https://github.com/vtothsvk/AP-Home.git
Cloning into 'AP-Home'...

remote: Enumerating objects: 217, done.
remote: Counting objects: 100% (217/217), done.
remote: Compressing objects: 100% (191/191), done.
remote: Total 217 (delta 129), reused 54 (delta 25), pack-reused 0R
Receiving objects: 100% (217/217), 58.08 KiB | 914.00 KiB/s, done.
Resolving deltas: 100% (129/129), done.

C:Users\[yourUsername]\MySuperDuperProject>
```

**3.**  Open your cloned repo and make yourself at home

```
C:Users\[yourUsername]\MySuperDuperProject> cd AP-Home

C:Users\[yourUsername]\MySuperDuperProject\AP-Home> 
```

**Voilà all set and done ^^**

Now u can start managing the git repo

### Updating your local repo

A new version of the source code is online and dont want to go to all the hassle of manually updating all the relevant files?
Behold the **pull** command

```
*inside your cloned local repo
git pull
```
eg.

```
C:\Users\epic_\mySuperDuperProject\AP-Home> git pull

remote: Enumerating objects: 9, done.
remote: Counting objects: 100% (9/9), done.
remote: Compressing objects: 100% (5/5), done.
remote: Total 5 (delta 3), reused 0 (delta 0), pack-reused 0
Unpacking objects: 100% (5/5), 1.27 KiB | 72.00 KiB/s, done.
From https://github.com/vtothsvk/AP-Home
   4b606a7..e1124ed  main       -> origin/main
   8fef733..9a07a15  pairTest   -> origin/pairTest
Updating 4b606a7..e1124ed
Fast-forward
 README.md | 64 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 64 insertions(+)
 
C:\Users\epic_\mySuperDuperProject\AP-Home>
```

**Done! your local repo is up to date ^^** 

### Branching

Wanna change the code but fear screwing up the programme? Git lets u create a **branch** of your code that u can edit independently of the
original source code.

### Creating a branch

```
*inside a git repo
git branch [yourBranchName]
```

### "Switching" branches

Now that u have created a branch u have to "check out" to it (by checking out u basically select the branch u are working on)

```
*inside a git repo
git checkout [yourBranchName]
```

### Listing all branches

Not sure about the branch u are working on or wanna check out but forgot the branch name?

```
*inside a git repo
git branch -a
```

The command prints out all available branches and higligths the one u are curenntly check out to.

### Checking out to a local branch of a remote repo

Git clone has a mysterious way of displaying locally cached branches lets see an example.

I cloned the AP-Home repo that has 2 branches "main" and "pairTest". Let's check which branches are chached locally.

```
C:\Users\epic_\mySuperDuperProject\AP-Home>git branch -a

* main
  remotes/origin/HEAD -> origin/main
  remotes/origin/main
  remotes/origin/pairTest
  
C:\Users\epic_\mySuperDuperProject\AP-Home>
```

Hmm, curious, it seems only the "main" branch is in my local repo. Truth is however, that Git caches all the remote branches locally, but
does not display them util I check out to them. So I see the remote repo has a branch "pairTest", that means I should have an
equally named branch in my local repo as well. Let's try it out...

```
C:\Users\epic_\mySuperDuperProject\AP-Home>git checkout pairTest
Switched to a new branch 'pairTest'
Branch 'pairTest' set up to track remote branch 'pairTest' from 'origin'.

C:\Users\epic_\mySuperDuperProject\AP-Home>git branch -a
  main
* pairTest
  remotes/origin/HEAD -> origin/main
  remotes/origin/main
  remotes/origin/pairTest

C:\Users\epic_\mySuperDuperProject\AP-Home>
```

Noice!

### "Saving" progress on your current branch

U can **"save"** your progress to the current branch by the **git commit** command. First tho, u have to **stage**
all of your changes by the **git add** command.

* git add

```
*inside a git repo
git add .
```

This command stages all changes to all files inside a repo

```
*inside a git repo
git commit --all -m "Your commit message"
```

This command commits all staged changes with a **commit message**
A commit message is a way of communicating what changed in the current commit eg. "Fixed incorrect pin initialisation".

### "Uploading" changes

To **"upload"** any local repo changes the **git push** command is used. (All your changes has to be locally commited first!)

```
*inside a locally cahced remote repo
git push
```

This command "pushes" all your locall changes to their tracked remote repo.

## Git visual GUI GitKraken

U can, alternatively, use the visual GUI for Git SCM - GitKraken

https://www.gitkraken.com/download

![Image of GitKraken](https://i.ibb.co/hFpbYmR/Git-Kraken.png)

## Git repo workflow

**We do not make direct changes to the "main" branch!!!**

In case of developing a new feature, a bug fix or any other shinanigans we follow the workflow shown below.

![Image of Git Workflow](https://i.ibb.co/vZ2ZxC5/Git-Workflow.png)

eg.

Let's create a rudimentary feature that makes the AP-node print out a line in a serial terminal.

**1. Clone/pull**

Clone the repo or pull if u just need to update the repo (It is essential to have ur local repo up to date with the remote one
because u can break older commits with your push)

```
C:\Users\epic_\mySuperDuperProject\AP-Home> git pull
remote: Enumerating objects: 6, done.
remote: Counting objects: 100% (6/6), done.
remote: Compressing objects: 100% (6/6), done.
remote: Total 6 (delta 2), reused 0 (delta 0), pack-reused 0
Unpacking objects: 100% (6/6), 5.29 KiB | 285.00 KiB/s, done.
From https://github.com/vtothsvk/AP-Home
   cc33435..f2a1444  main       -> origin/main
Already up to date.

C:\Users\epic_\mySuperDuperProject\AP-Home>
```

**2. Branch off and check out**

Create your local branch and check out to it

```
C:\Users\epic_\mySuperDuperProject\AP-Home> git branch newFeatureTest

C:\Users\epic_\mySuperDuperProject\AP-Home> git checkout newFeatureTest
Switched to branch 'newFeatureTest'

C:\Users\epic_\mySuperDuperProject\AP-Home>
```

(alternatively u can carry out both steps in one command by using **git checkout -b [newBranchName]**)

**3. Edit the code**

**4. Commit your changes**

```
C:\Users\epic_\mySuperDuperProject\AP-Home> git commit --all -m "added a new booting message"
[newFeatureTest 2139e4a] added a new booting message
 1 file changed, 2 insertions(+)

C:\Users\epic_\mySuperDuperProject\AP-Home>
```

**5. Push**

Push your branch to the remote repo using the **git push** command adding **--set-upstream origin [newBranchName]**

```
C:\Users\epic_\mySuperDuperProject\AP-Home> git push --set-upstream origin newFeatureTest
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 351 bytes | 351.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
remote:
remote: Create a pull request for 'newFeatureTest' on GitHub by visiting:
remote:      https://github.com/vtothsvk/AP-Home/pull/new/newFeatureTest
remote:
To https://github.com/vtothsvk/AP-Home.git
 * [new branch]      newFeatureTest -> newFeatureTest
Branch 'newFeatureTest' set up to track remote branch 'newFeatureTest' from 'origin'.

C:\Users\epic_\mySuperDuperProject\AP-Home>
```

**6. Create a pull request**

1. Openinng the repo in github navigate to the **Pull requests** tab

![Image of Pull request 1](https://i.ibb.co/x2Fj9wn/pull-Req-Tab.png)

2. Create a **new pull request**

![Image of Pull request 2](https://i.ibb.co/7GgJtQk/newPReq.png)

3. Select the branch u want to merge into the "main* branch
(In this case its the "newFeatureTest" branch)

![Image of Pull request 3](https://i.ibb.co/9WWMjYt/select-Branch.png)

4. Check changes made in the selected branch and then continue as shown in the image

![Image of Pull request 4](https://i.ibb.co/xLLqtrM/compare.png)

5. Describe your pull request and finally create your pull request

![Image of Pull request 5](https://i.ibb.co/vPnsPMp/final.png)

**Congrats!! the rest of the work is my business :P**

**7. Deleting a branch**

To delete a branch on local repository use command **git branch -d [name_of_branch]**

```
C:\Users\epic_\mySuperDuperProject\AP-Home> git branch -d name_of_branch

warning: deleting branch 'name_of_branch' that has been merged to
         'refs/remotes/origin/name_of_branch', but not yet merged to HEAD.
Deleted branch name_of_branch (was 4955ffd).
```

To delete a branch on remote repository use command **git push origin --delete [name_of_branch]**

```
C:\Users\epic_\mySuperDuperProject\AP-Home> git push origin --delete name_of_branch

To https://github.com/vtothsvk/AP-Home
 - [deleted]         name_of_branch
 ```

## Git Issues

Encountered a bug or u have an idea u want to contribute to the project? Create **Git Issue**

### Creating an issue

Let's crete a **bug report** issue for a reference

1. U navigate to the **Issues** tab in github

![Iamge of Issues tab](https://i.ibb.co/WGk983S/issue-tab.png)

2. Create **New issue**

![Image of New Issue](https://i.ibb.co/fGcXVxm/new-issue.png)

3. Select the **Bug report** template

![Image of Template selection](https://i.ibb.co/ZH7DZVh/bug-repotr-select.png)

4. Complete your issue

![Image of Complete your issue](https://i.ibb.co/HTsCb25/issue-submit.png)

**Voilà all set and done ^^** u can now see your issue under the open issues.

![Image of Open issues](https://i.ibb.co/mcgWs8N/Open-issues.png)

![Image of Your new issue](https://i.ibb.co/dc8YhQs/issue-created.png)

Feel free to browse through all the open a close issues any time ur in need of help or inspirtion creating an issue.

## Git project management

Git issues have more perks than at first glance may seem. If understand as tasks, they can be organised into **projects**. 
Github supports various project management methods (for example [Kanban](https://en.wikipedia.org/wiki/Kanban_(development))) by which git issues can be handled.
Check out the [projects](https://github.com/vtothsvk/AP-Home/projects) tab for more info.

## Formatting text - Markdown
Comments, issues and virtually every other text on github uses [Markdown](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet) formating and syntax. 
* [Mastering Markdown](https://guides.github.com/features/mastering-markdown/)
