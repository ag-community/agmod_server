ag = {
    warnings_as_errors = get_config("warnings_as_errors") == true,
}

-- Included files run from their own directory.
function ag.path(rel)
    return path.join(os.projectdir(), rel)
end
