# Repository Guidelines

## Project Structure & Module Organization

This repository is a static personal blog published as HTML. Org-mode sources are
the primary content: `index.org` is the home page, and posts live in
`Programming/`, `Medicine/`, and `Hobbies/`. Images belong in the nearest
`images/` directory; shared assets are in `Images/`, `lib/js/`, and
`readtheorg_theme/`. 

The shared Org export configuration is `html-theme-readtheorg-local.setup`. 
`Programming/src/` contains the C++ sample used by the memory-order article, while `docs/` holds the downloadable CV.

## Build, Test, and Development Commands

Do NOT build this project or run tests.

There is no package manager, site generator, or automated test suite. 

## Coding Style & Naming Conventions

Preserve existing Org conventions: a `#+SETUPFILE` near the top, a descriptive `#+TITLE`, and relative `file:`
links for local content. 

Do not hand-edit generated HTML unless the change is deliberately HTML-only; normally update the `.org` file. 

Exporting `.html` files must be done by the user exclusively, always. 
Preserve root-relative `/trada/` paths used by the shared theme. 

Follow the existing C++ style: four-space indentation, braces on the declaration line, 
`std::` names, and C++20 facilities.

## Citations & References

When citing a repository file in a response, include its exact line number. 
Use a file-and-line reference such as `path/to/file.org:42`; do not cite a file without a line number.

## Testing Guidelines

Do NOT try to create or run tests.

## Commit & Pull Request Guidelines

Do NOT create a commit or pull request.
Only the repository author may create commits and pull requests.




