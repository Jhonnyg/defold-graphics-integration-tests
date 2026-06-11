#!/usr/bin/env python3

import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path


def find_projects(root):
    return sorted(path.parent for path in root.glob("*/game.project"))


def build_project(project_dir, bob_path, clean):
    if clean:
        shutil.rmtree(project_dir / "build", ignore_errors=True)

    command = [
        "java",
        "-jar",
        str(bob_path),
        "--debug-output-spirv=true",
        "resolve",
        "build",
    ]
    return subprocess.run(command, cwd=project_dir).returncode


def main():
    parser = argparse.ArgumentParser(description="Build all graphics integration test projects.")
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parent)
    parser.add_argument("--keep-build", action="store_true", help="Do not delete project build folders before building.")
    args = parser.parse_args()

    dynamo_home = os.getenv("DYNAMO_HOME")
    if not dynamo_home:
        print("No DYNAMO_HOME specified.", file=sys.stderr)
        return 1

    bob_path = Path(dynamo_home) / "share" / "java" / "bob.jar"
    if not bob_path.is_file():
        print(f"Could not find bob.jar at {bob_path}", file=sys.stderr)
        return 1

    root = args.root.resolve()
    projects = find_projects(root)
    if not projects:
        print(f"No game.project files found under {root}", file=sys.stderr)
        return 1

    failures = []
    for index, project_dir in enumerate(projects, 1):
        name = project_dir.relative_to(root)
        print(f"\n[{index}/{len(projects)}] Building {name}", flush=True)
        returncode = build_project(project_dir, bob_path, clean=not args.keep_build)
        if returncode != 0:
            failures.append((name, returncode))
            print(f"FAILED {name} ({returncode})", flush=True)
        else:
            print(f"OK {name}", flush=True)

    print("\nBuild summary")
    print(f"  OK: {len(projects) - len(failures)}")
    print(f"  Failed: {len(failures)}")
    for name, returncode in failures:
        print(f"  - {name} ({returncode})")

    return 1 if failures else 0


if __name__ == "__main__":
    sys.exit(main())
