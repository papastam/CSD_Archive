
###################################################
#
# file: Makefile
#
# @Author:   Iacovos G. Kolokasis
# @Version:  10-02-2021
# @email:    kolokasis@csd.uoc.gr
#
# Makefile
#
####################################################

## Do not touch here
turnin: undoTurnin
	-git tag assignment5
	-git push origin --tags

undoTurnin:
	if git tag --list | egrep -q "assignment5"; then \
		git tag -d assignment5 && git push origin :refs/tags/assignment5; \
		fi
