# problems encountered when using git

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

## origin

We often use `origin` in git command. So what is `origin`? `origin` is an alias for your remote repository, and by default, `origin` represents the repository you cloned.

- `git remove -v`: show the relationship between the alias and remote repository
- `git remote add <alias> <remote repository>`: add the relationship between the alias and remote repository

### reference

- [Git里面的origin到底代表啥意思?](https://www.zhihu.com/question/27712995)

## master, origin/master, remote/origin/master

As the title, there are three different `master` in git:

- `master`: local branch
- `origin/master`: remote branch, sometimes we use `remote/origin/master` or `origin master` instead

### reference

- [Git branching: master vs. origin/master vs. remotes/origin/master](https://stackoverflow.com/questions/10588291/git-branching-master-vs-origin-master-vs-remotes-origin-master)



