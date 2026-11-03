# Overview

python code and templates to generate vectorized reduction routines

# Files

| File                      | Description                                         |
|---------------------------|-----------------------------------------------------|
| misc                      | miscelaneous files, not for deployment              |
| intrinsisc.jinja2         | template file to render vector code                 |
| root.jinja2               | root file for rendering to vector_reduce_*type*.c   |
| profiles.py               | Profiles to configure vector instructions and types |
| gccsimd.jinja2            | template file for GCC SIMD vector instructions      |
| varargsreduce.jinja2      | template file for variadic argument reduction       |
| varargsreduce_simd.jinja2 | template file for SIMD variadic argument reduction  |
