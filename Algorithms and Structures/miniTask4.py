import subprocess
import shlex

import os

def command_miniTask(hash):
    checkout(hash)

    filename = "miniTask3.py"
    filepath = "Algorithms and Structures"

    args = ["python", f"{filepath}/{filename}"]

    try:
        p = subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
    except Exception:
        return 1
    return 0

def search(commits, command):
    left = 0
    right = len(commits) - 1
    res_ind = -1
    it_ind = right // 2
    error_code = command(commits[it_ind])

    while True: 
        if left >= right:
            break

        if error_code != 0:
            if it_ind == len(commits) - 1 or command(commits[it_ind + 1]) == 0:
                res_ind = it_ind
                break
            left = it_ind

        elif error_code == 0:
            if it_ind == 0 or command(commits[it_ind - 1]) != 0:
                res_ind = it_ind
                break
            right = it_ind
        it_ind = (left + right) // 2
        error_code = command(commits[it_ind])

    return res_ind


def checkout(hash):
    cmd = f'git checkout {hash}'
    args = shlex.split(cmd)

    subprocess.Popen(args, stdout=subprocess.PIPE)

def git_log(start_hash, end_hash):
    cmd = f'git log {start_hash}..{end_hash}'
    args = shlex.split(cmd)

    p = subprocess.Popen(args, stdout=subprocess.PIPE)
    out_list = p.communicate()[0].splitlines(keepends=True)

    out_list = [i.decode(encoding="utf-8") for i in out_list]
    out_list = [''.join(out_list[i:i+6]) for i in range(0, len(out_list), 6)]

    return out_list


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

    start_hash = "cd1ac44bca84436ae78d5a0bee0fc9e1c1511b8a"
    end_hash = "54fddbdf940e42b362b1fd9b6f4862301516add2"

    command = command_miniTask

    bad_commit = bisect(rep_path, start_hash, end_hash, command)

    checkout("54fddbdf940e42b362b1fd9b6f4862301516add2")

    print(bad_commit)