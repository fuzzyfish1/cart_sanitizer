from django.shortcuts import render
from django.http import HttpResponse

# create your own views here

def index(request):
	return HttpRespinse("Hello, world. you are at polls index")
