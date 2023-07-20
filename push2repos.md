**Message for push2repos.md**

To streamline the process of pushing your code changes to multiple remote repositories, you can use one of the following methods. These methods will allow you to easily push your commits to both GitHub and GitLab repositories simultaneously:

**Method 1: Using post-push Git Hook**

Create a file named `.git/hooks/post-push` in your project's root directory and add the following content to it:

```bash
#!/bin/sh

# Push to the GitHub repository
git push github $@

# Push to the GitLab repository
git push gitlab $@
```

Remember to make the script executable with the following command:

```bash
chmod +x .git/hooks/post-push
```

**Method 2: Using Git Config Alias**

Add the following lines to your `.gitconfig` file:

```bash
[alias]
    pushall = !sh -c 'git push github $1 && git push gitlab $1' -
```

Now, you can push to both repositories using the following command:

```bash
git pushall <branch_name>
```

**Method 3: Using Custom Bash Script**

Create a file named `script_maison.sh` in your project's root directory and add the following content to it:

```bash
#!/bin/bash

# Replace 'github' and 'gitlab' with the actual remote names
remotes=("github" "gitlab")

# Push to all specified remotes
for remote in "${remotes[@]}"; do
    git push $remote $1
done
```

Make the script executable with the following command:

```bash
chmod +x script_maison.sh
```

Now, you can push to both repositories using the custom script:

```bash
./script_maison.sh <branch_name>
```

Choose the method that best fits your workflow, and it will allow you to easily push your code to both GitHub and GitLab repositories with a single command. Happy coding!