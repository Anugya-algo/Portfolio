# Anugya's Portfolio

This is a simple static portfolio website intended for deployment on GitHub Pages.

Quick deploy (GitHub Pages - branch: `main` or `gh-pages`):

1. Commit and push this repository to GitHub.
2. In GitHub, go to Settings → Pages and select the branch (`main` or `gh-pages`) and root (`/`) as the source.
3. Save — your site will be published at `https://<your-username>.github.io/<repo-name>/`.

Notes:
- All asset paths are relative and use forward slashes so they work on case-sensitive servers.
- `index.html` is the site entry point.
- If you are deploying with Netlify from the repo root, this repo uses a nested publish folder. The included `netlify.toml` sets `publish = "project2"`.
- If you use a custom domain, add a `CNAME` file with your domain.

Local preview:
Open `index.htm` in a browser, or run a simple HTTP server from this folder:

```bash
# Python 3
python -m http.server 8000
# Then visit http://localhost:8000
```
