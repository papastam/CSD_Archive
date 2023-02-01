
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
	-git tag assignment6
	-git push origin --tags

undoTurnin:
	if git tag --list | egrep -q "assignment6"; then \
		git tag -d assignment6 && git push origin :refs/tags/assignment6; \
		fi

