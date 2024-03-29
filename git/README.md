# git

- [checkout branch when uncommitted](https://github.com/gaoxinge/something/tree/master/git#checkout-branch-when-uncommitted)
- [origin](https://github.com/gaoxinge/something/tree/master/git#origin)
- [master, origin/master, remote/origin/master](https://github.com/gaoxinge/something/tree/master/git#master-originmaster-remoteoriginmaster)
- [git command related with remote](https://github.com/gaoxinge/something/tree/master/git#git-command-related-with-remote)
- [git pull vs git fetch](https://github.com/gaoxinge/something/tree/master/git#git-pull-vs-git-fetch)
- [how to push amend commit to remote](https://github.com/gaoxinge/something/tree/master/git#how-to-push-amend-commit-to-remote)
- [cancel](https://github.com/gaoxinge/something/tree/master/git#cancel)
- [how to exit git diff or git log](https://github.com/gaoxinge/something/tree/master/git#how-to-exit-git-diff-or-git-log)
- [difference between git checkout -- and git checkout](https://github.com/gaoxinge/something/tree/master/git#difference-between-git-checkout----and-git-checkout)
- [git diff](https://github.com/gaoxinge/something/tree/master/git#git-diff)
- [connecting to github with ssh](https://github.com/gaoxinge/something/tree/master/git#connecting-to-github-with-ssh)
- [配置](https://github.com/gaoxinge/something/tree/master/git#%E9%85%8D%E7%BD%AE)

## checkout branch when uncommitted

It often happens that you should fix bugs on master, when writing codes on a dev branch. However you don't want to commit codes right now, and just checkout branch. Then changes on dev branch will follow you to master, or some conflits will leave you on dev branch.

Why this happens? To answer this question, we should know the mechanics of the git. 

- `.git` is a local database to record the info of branches and commits, and when you checkout branch, `.git` will retrieve info of the target branch.
- If you uncommit changes, the changes will not be recorded in the `.git`.

So it is easy to see how git protects you from changing files carelessly without recording changes to local database. To solve this problem, only we should do is to commit changes, chekcout branch and when you come back, retrieve the uncommitted state.

- `git stash`: commit all the changes, but on no branch at all
- `git stash apply`: get the changes back

### reference

- [1.3 Getting Started - Git Basics](https://git-scm.com/book/en/v2/Getting-Started-Git-Basics)
- [Checkout another branch when there are uncommitted changes on the current branch](https://stackoverflow.com/questions/22053757/checkout-another-branch-when-there-are-uncommitted-changes-on-the-current-branch)
- [See what's in a stash without applying it](https://stackoverflow.com/questions/10725729/see-whats-in-a-stash-without-applying-it)
- [git stash 命令](http://blog.csdn.net/longxiaowu/article/details/26815433)

## origin

We often use `origin` in git command. So what is `origin`? `origin` is an alias for your remote repository, and by default, `origin` represents the repository you cloned.

- `git remove -v`: show the relationship between the alias and remote repository
- `git remote add <alias> <remote repository>`: add the relationship between the alias and remote repository

### reference

- [Git里面的origin到底代表啥意思?](https://www.zhihu.com/question/27712995)

## master, origin/master, remote/origin/master

As the title, there are three different `master` in git:

- `master`: local branch
- `origin/master`: remote branch, sometimes we use `remote/origin/master` instead

### reference

- [Git branching: master vs. origin/master vs. remotes/origin/master](https://stackoverflow.com/questions/10588291/git-branching-master-vs-origin-master-vs-remotes-origin-master)

## git command related with remote

- `git clone https://github.com/gaoxinge/something`
- `git push`: same as `git push origin master: master` (first is local, second is remote)
- `git fetch`: get all changes in remote to local repository, and then use merge to fresh local branch
- `git pull`: same as `git pull origin master: master` (first is remote, second is local)

### reference

- [Git远程操作详解](http://www.ruanyifeng.com/blog/2014/06/git_remote.html)

## git pull vs git fetch

For simply, `git pull` = `git fetch` + `git merge`. Some somebody will recommand

```
Don't use git pull, use git fetch and then git merge.
```

for `git fetch` is more clear and safe than `git pull`. However we sometimes will use the `git pull` for convenience. But there will be some problems in this situation.

### when nobody pushed changes to remote

```
> git pull # safe
```

### when someone pushed changes to remote, and you have committed your changes in local

```
> echo 'hello world' >> README.md
> git commit -am "add hello world in readme"
```

So when you pull from remote, there may be some conflicts, and you have to deal with them by your own hand.

```
> git pull
> vi README.md
```

### when someone pushed changes to remote, and your have't committed your changes in local

```
> echo 'hello world' >> README.md
```

So when you pull from remote, there will be error. This is because the git protects the merge from covering your changes. However this pull will fetch the change in remote to local repository, and you can deal with this like:

```
> git commit -am "add hello world in readme"
> git merge origin/master
> vi README.md
```

### reference

- [What is the difference between 'git pull' and 'git fetch'](https://stackoverflow.com/questions/292357/what-is-the-difference-between-git-pull-and-git-fetch)

## how to push amend commit to remote

This push's response is different from git push without commit:

- `git commit --amend` & `git push`: rejected
- `git push`: everything up-to-date

The solution to solve this problem looks dirty:

- `git push -f origin master`
- `git push origin :master` & `git push origin master`

### reference

- [How do I push amended commit to the remote Git repository](https://stackoverflow.com/questions/253055/how-do-i-push-amended-commit-to-the-remote-git-repository)

## cancel

### modified

```
> echo 'hello world' >> README.md
> git checkout -- README.md
```

### stage

```
> echo 'hello world' >> README.md
> git add "add hello world in readme"
> git reset HEAD README.md
```

### commit

```
> echo 'hello world' >> README.md
> git commit -am "add hello world in readme"
> git reset --hard HEAD^
```

### reference

- [How to revert Git repository to a previous commit](https://stackoverflow.com/questions/4114095/how-to-revert-git-repository-to-a-previous-commit)

## how to exit `git diff` or `git log`

Please pressing `q` to quit instead of `ctrl-c`. 

## difference between `git checkout --` and `git checkout`

Please using `git checkout --` to recover file, and `git checkout` to change branch.

### reference

- [git checkout — . vs git checkout](https://stackoverflow.com/questions/41101998/git-checkout-vs-git-checkout)

## git diff

- `git diff`: compare two latest commits of local branches
- `git diff [branch1] [branch2]`: compare details of two branches
- `git diff [branch1] [branch2] --stat`: compare stat of two branches
- `git diff [branch1] [branch2] --name-status`: compare name status of two branches
- `git diff [branch1] [branch2] [file]`: compare same file of two branches

## connecting to github with ssh

- generate ssh key at local: `ssh-keygen -t ed25519 -C "your_email@example.com"`
- copy ssh key at local: `cat ~/.ssh/id_ed25519.pub`
- add ssh key at remote: `Settings` -> `SSH and GPG keys` -> `New SSH Key`
  - Set `Title` to specific the develop environment
  - Set `Key Type` to default
  - Set `Key` with the copy value

### reference

- [Connecting to GitHub with SSH](https://docs.github.com/en/authentication/connecting-to-github-with-ssh)

## 配置

### ide

在ide的file -> settings -> tools -> terminal的Shell Path里设置`D:\Git\bin\base.exe`

### 中文

在`~/.vimrc`中添加

```
set encoding=utf-8
set termencoding=utf-8
set fileencodings=utf-8
```

在`~/.bashrc`中添加

```
export LANG=en_US.utf-8
alias ls='ls --show-control-chars --color=auto'
```

### 代理

在`~/.bashrc`中添加

```
export http_proxy=http://127.0.0.1:80
export https_proxy=http://127.0.0.1:80
export no_proxy=github.com
```

### reference

- [打造完美 Windows git 命令行 环境](https://www.v2ex.com/t/154202)
