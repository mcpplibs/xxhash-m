#!/usr/bin/env python3
"""Run xxHash's own tests/sanity_test.c (of the release) against compat.xxhash
0.8.3, the library this wrapper exports.

The release tarball is downloaded once into target/upstream and checked
against upstream/documents.json. tests/sanity_test.c, its vectors and the
cli/xsum_* files it includes are copied into target/conformance, with one
change: upstream's test defines XXH_IMPLEMENTATION, which compiles a private
copy of xxHash into the test; the copy replaces that definition with the two
C headers it brought in, so that every hash is computed by compat.xxhash. It
checks XXH32, XXH64, XXH3-64 and XXH3-128, one-shot and streaming, with seeds
and secrets, against upstream's 49948 vectors, and must end with status 0.
"""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tarfile
import urllib.request

MANIFEST = '''[package]
name        = "xxhash-conformance"
version     = "0.8.3"
description = "xxHash 0.8.3's tests/sanity_test.c over compat.xxhash (tools/run_conformance.py)"

[targets.sanity_test]
kind = "bin"
main = "tests/sanity_test.c"

[build]
c_standard = "c11"
sources    = []
# cli/xsum_os_specific.c uses fileno(), which ISO C does not declare.
cflags     = ["-D_POSIX_C_SOURCE=200809L"]

[dependencies]
compat.xxhash = "0.8.3"
'''

IMPLEMENTATION = '#define XXH_IMPLEMENTATION   /* access definitions */\n'
LIBRARY = '#include <stdlib.h>  /* xxhash-m: the hashes are compat.xxhash\'s, not a copy in this unit */\n#include <string.h>\n'


def fetch(root: Path) -> Path:
    pins = json.loads((root / 'upstream/documents.json').read_text(encoding='utf-8'))
    cache = root / 'target/upstream'
    cache.mkdir(parents=True, exist_ok=True)
    archive = cache / 'xxhash-release.tar.gz'
    if not archive.exists() or hashlib.sha256(archive.read_bytes()).hexdigest() != pins['upstream_sha256']:
        print('+ fetch', pins['upstream'], flush=True)
        with urllib.request.urlopen(pins['upstream'], timeout=120) as response:
            archive.write_bytes(response.read())
    digest = hashlib.sha256(archive.read_bytes()).hexdigest()
    if digest != pins['upstream_sha256']:
        sys.exit(f'upstream archive checksum {digest} != {pins["upstream_sha256"]}')
    with tarfile.open(archive) as tar:
        top = tar.getmembers()[0].name.split('/')[0]
        if not (cache / top).exists():
            tar.extractall(cache, filter='data')
    return cache / top


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--mcpp', default='mcpp')
    parser.add_argument('--toolchain')
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    upstream = fetch(root)
    work = root / 'target/conformance'
    shutil.rmtree(work, ignore_errors=True)
    (work / 'tests').mkdir(parents=True)
    (work / 'cli').mkdir()
    for name in ('xxhash.h', 'xxh3.h'):
        shutil.copyfile(upstream / name, work / name)
    for path in (upstream / 'cli').glob('xsum_*'):
        shutil.copyfile(path, work / 'cli' / path.name)
    shutil.copyfile(upstream / 'tests/sanity_test_vectors.h', work / 'tests/sanity_test_vectors.h')
    test = (upstream / 'tests/sanity_test.c').read_text(encoding='utf-8')
    if test.count(IMPLEMENTATION) != 1:
        sys.exit('tests/sanity_test.c no longer defines XXH_IMPLEMENTATION once; review the change')
    (work / 'tests/sanity_test.c').write_text(test.replace(IMPLEMENTATION, LIBRARY), encoding='utf-8')
    (work / 'mcpp.toml').write_text(MANIFEST, encoding='utf-8')
    build = [args.mcpp, 'build', '--release']
    if args.toolchain:
        build += ['--toolchain', args.toolchain]
    print('+', ' '.join(build), flush=True)
    subprocess.run(build, cwd=work, check=True)
    test = next(p for p in (work / 'target').rglob('sanity_test*') if p.is_file() and p.suffix in ('', '.exe'))
    print('+', test, flush=True)
    subprocess.run([test], cwd=work, check=True)
    print('xxHash 0.8.3: tests/sanity_test.c passed over compat.xxhash', flush=True)


if __name__ == '__main__':
    main()
