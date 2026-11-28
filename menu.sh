#!/bin/bash


REPO_RAW="https://raw.githubusercontent.com/11niya11/OS-Practical-Kit/main"
WORKDIR="$HOME/os_viva_run"
mkdir -p "$WORKDIR" && cd "$WORKDIR"

# Sample files for file-management & copy programs
printf "apple\nbanana\ncherry\n" > f1.txt
printf "apple\nblueberry\ncherry\ndate\n" > f2.txt

ITEMS=(
  "01_linux_commands.sh|sh|linux commands wc clear cal who date pwd cd mkdir rmdir ls chmod chown chgrp"
  "02_process_commands.sh|sh|process commands fork getpid ps kill sleep redirection pipe"
  "03_fork_exec.c|c|fork exec wait parent child process"
  "04_cpu_info.c|c|kernel version cpu type model uname proc cpuinfo"
  "05_memory_info.c|c|memory configured free used meminfo"
  "06_file_copy.c|c|copy files system call open read write close"
  "07_os_simulator.md|md|simulator oscope"
  "08_fcfs.c|c|fcfs first come first serve scheduling"
  "09_sjf.c|c|sjf shortest job first scheduling"
  "10_srtf.c|c|srtf shortest remaining time first scheduling"
  "11_priority.c|c|priority scheduling non preemptive"
  "12_pthreads_sum.c|pthread|pthreads sum threads"
  "13_memory_allocation.c|c|first fit best fit worst fit memory allocation"
)

run_one() {
  local idx="$1"
  IFS='|' read -r file kind _ <<< "${ITEMS[$idx]}"
  echo ""
  echo ">>> Downloading & running: $file <<<"
  curl -fsSL "$REPO_RAW/$file" -o "$file"

  if [ "$kind" = "sh" ]; then
    chmod +x "$file"
    bash "$file"
  elif [ "$kind" = "c" ]; then
    local bin="${file%.c}"
    gcc "$file" -o "$bin" -lm
    ./"$bin"
  elif [ "$kind" = "pthread" ]; then
    local bin="${file%.c}"
    gcc "$file" -o "$bin" -lpthread -lm
    ./"$bin"
  else
    cat "$file"
  fi
}

find_matches() {
  local query
  query=$(echo "$1" | tr '[:upper:]' '[:lower:]')
  local matches=()

  # If user typed a number 1..13
  if [[ "$query" =~ ^[0-9]+$ ]] && [ "$query" -ge 1 ] && [ "$query" -le "${#ITEMS[@]}" ]; then
    matches+=($((query - 1)))
    echo "${matches[@]}"
    return
  fi

  for i in "${!ITEMS[@]}"; do
    local hay
    hay=$(echo "${ITEMS[$i]}" | tr '[:upper:]' '[:lower:]')
    if [[ "$hay" == *"$query"* ]]; then
      matches+=("$i")
    fi
  done
  echo "${matches[@]}"
}

# If argument passed directly to command (e.g., ... | bash -s fcfs)
if [ "$#" -gt 0 ]; then
  q="$*"
  if [ "$q" = "all" ]; then
    for i in "${!ITEMS[@]}"; do run_one "$i"; done
    exit 0
  fi
  m=($(find_matches "$q"))
  if [ "${#m[@]}" -eq 0 ]; then
    echo "No match found for: $q"
    exit 1
  fi
  for idx in "${m[@]}"; do run_one "$idx"; done
  exit 0
fi

# Interactive Menu Loop
while true; do
  echo ""
  echo "================ OS PRACTICAL MENU ================"
  for i in "${!ITEMS[@]}"; do
    IFS='|' read -r file _ _ <<< "${ITEMS[$i]}"
    printf "%2d) %s\n" "$((i + 1))" "$file"
  done
  echo " a) Run ALL"
  echo " q) Quit"
  echo "---------------------------------------------------"
  read -r -p "Enter number, 'a', or type question/keyword (e.g. fcfs, fork, pthread, fit): " choice

  case "$choice" in
    q|Q) break ;;
    a|A)
      for i in "${!ITEMS[@]}"; do run_one "$i"; done
      ;;
    *)
      m=($(find_matches "$choice"))
      if [ "${#m[@]}" -eq 0 ]; then
        echo "Koi match nahi mila '$choice' ke liye. Dobara try karo."
      elif [ "${#m[@]}" -eq 1 ]; then
        run_one "${m[0]}"
      else
        echo "Multiple matches mile:"
        for idx in "${m[@]}"; do
          IFS='|' read -r file _ _ <<< "${ITEMS[$idx]}"
          echo "  $((idx + 1))) $file"
        done
        read -r -p "Kaunsa number run karna hai? " pick
        if [[ "$pick" =~ ^[0-9]+$ ]] && [ "$pick" -ge 1 ] && [ "$pick" -le "${#ITEMS[@]}" ]; then
          run_one $((pick - 1))
        fi
      fi
      ;;
  esac
done
