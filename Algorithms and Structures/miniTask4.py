import subprocess
import shlex

import os

def command(hash):
    checkout(hash)

    filename = "miniTask3.py"
    filepath = "Algorithms and Structures"

    cmd = f"python {filepath}/{filename}"
    args = shlex.split(cmd)

    p = subprocess.Popen(args, stderr=subprocess.PIPE)
    stderr = p.communicate()[1].decode(encoding="utf-8")
    if not stderr:
        return 1
    else:
        return 0

def search(commits, command):
    left = 0
    right = len(commits)
    res_ind = -1
    it_ind = right // 2
    error_code = command(commits[it_ind])

    while True: 
        if left >= right:
            break

        if error_code != 0:
            if command(commits[it_ind + 1] == 0):
                res_ind = it_ind
                break
            left = it_ind

        elif error_code == 0:
            if command(commits[it_ind - 1] != 0):
                res_ind = it_ind
                break
            right = it_ind
        it_ind = (left + right) // 2
        error_code = command(commits[it_ind])

    return res_ind


def checkout(hash):
    cmd = f'git checkout {hash}'
    args = shlex.split(cmd)

    subprocess.Popen(args)

def git_log(start_hash, end_hash):
    cmd = f'git log {start_hash}..{end_hash}'
    args = shlex.split(cmd)

    p = subprocess.Popen(args, stdout=subprocess.PIPE)
    out_list = p.communicate()[0].splitlines(keepends=True)

    out_list = [i.decode(encoding="utf-8") for i in out_list]
    out_list = [''.join(out_list[i:i+6]) for i in range(0, len(out_list), 6)]

    return out_list[::-1]


def bisect(rep_path, start_hash, end_hash, command):
    
    old_path = os.getcwd()
    os.chdir(rep_path)

    logs = git_log(start_hash, end_hash)

    commits = [log.splitlines()[0].split()[1] for log in logs] 

    commit = search(commits, command)

    os.chdir(old_path)

    return commit


if __name__ == "__main__":
    rep_path = "D:/Documents/Coding/Visual Studio Code Projects/Studying"
    

