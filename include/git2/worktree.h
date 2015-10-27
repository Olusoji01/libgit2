/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_git_worktree_h__
#define INCLUDE_git_worktree_h__

#include "common.h"
#include "buffer.h"
#include "types.h"
#include "strarray.h"

/**
 * @file git2/worktrees.h
 * @brief Git worktree related functions
 * @defgroup git_commit Git worktree related functions
 * @ingroup Git
 * @{
 */
GIT_BEGIN_DECL

/**
 * List names of linked working trees
 *
 * The returned list should be released with `git_strarray_free`
 * when no longer needed.
 *
 * @param out pointer to the array of working tree names
 * @param repo the repo to use when listing working trees
 * @return 0 or an error code
 */
GIT_EXTERN(int) git_worktree_list(git_strarray *out, git_repository *repo);

/**
 * Lookup a working tree by its name for a given repository
 *
 * @param out Output pointer to looked up worktree or `NULL`
 * @param repo The repository containing worktrees
 * @param name Name of the working tree to look up
 * @return 0 or an error code
 */
GIT_EXTERN(int) git_worktree_lookup(git_worktree **out, git_repository *repo, const char *name);

/**
 * Free a previously allocated worktree
 *
 * @param wt worktree handle to close. If NULL nothing occurs.
 */
GIT_EXTERN(void) git_worktree_free(git_worktree *wt);

/**
 * Check if worktree is valid
 *
 * A valid worktree requires both the git data structures inside
 * the linked parent repository and the linked working copy to be
 * present.
 *
 * @param wt Worktree to check
 * @return 0 when worktree is valid, error-code otherwise
 */
GIT_EXTERN(int) git_worktree_validate(const git_worktree *wt);

/**
 * Add a new working tree
 *
 * Add a new working tree for the repository, that is create the
 * required data structures inside the repository and check out
 * the current HEAD at `path`
 *
 * @param out Output pointer containing new working tree
 * @param repo Repository to create working tree for
 * @param name Name of the working tree
 * @param path Path to create working tree at
 * @return 0 or an error code
 */
GIT_EXTERN(int) git_worktree_add(git_worktree **out, git_repository *repo, const char *name, const char *path);

/**
 * Lock worktree if not already locked
 *
 * Lock a worktree, optionally specifying a reason why the linked
 * working tree is being locked.
 *
 * @param wt Worktree to lock
 * @param reason Reason why the working tree is being locked
 * @return 0 on success, non-zero otherwise
 */
GIT_EXTERN(int) git_worktree_lock(git_worktree *wt, char *reason);

/**
 * Unlock a locked worktree
 *
 * @param wt Worktree to unlock
 * @return 0 on success, 1 if worktree was not locked, error-code
 *  otherwise
 */
GIT_EXTERN(int) git_worktree_unlock(git_worktree *wt);

/**
 * Check if worktree is locked
 *
 * A worktree may be locked if the linked working tree is stored
 * on a portable device which is not available.
 *
 * @param reason Buffer to store reason in. If NULL no reason is stored.
 * @param wt Worktree to check
 * @return 0 when the working tree not locked, a value greater
 *  than zero if it is locked, less than zero if there was an
 *  error
 */
GIT_EXTERN(int) git_worktree_is_locked(git_buf *reason, const git_worktree *wt);

/**
 * Flags which can be passed to git_worktree_prune to alter its
 * behavior.
 */
typedef enum {
	/* Prune working tree even if working tree is valid */
	GIT_WORKTREE_PRUNE_VALID = 1u << 0,
	/* Prune working tree even if it is locked */
	GIT_WORKTREE_PRUNE_LOCKED = 1u << 1,
	/* Prune checked out working tree */
	GIT_WORKTREE_PRUNE_WORKING_TREE = 1u << 2,
} git_worktree_prune_t;

/**
 * Prune working tree
 *
 * Prune the working tree, that is remove the git data
 * structures on disk. The repository will only be pruned of
 * `git_worktree_is_prunable` succeeds.
 *
 * @param wt Worktree to prune
 * @param flags git_worktree_prune_t flags
 * @return 0 or an error code
 */
GIT_EXTERN(int) git_worktree_prune(git_worktree *wt, unsigned flags);

/** @} */
GIT_END_DECL
#endif
