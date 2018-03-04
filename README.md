# mruby-stable-sort

rapidly stable sort for fixnum property by `qsort`.

short example:

```ruby
a = 1000.times.map{ rand(100) }
a.stable_sort(:to_i)
```

long example:

```ruby
class Node
  attr_accessor :z, :index
end

a = 50.times.map{|i|
  n = Node.new
  n.z = rand(10)
  n.index = i
  n
}

puts "----"
p a.map{|i| "#{i.z}:#{i.index}" }.join(", ")

puts "----"
start_at = Time.now
b = a.stable_sort :z
end_at = Time.now
elapse = (end_at - start_at)*1000
puts "sort #{elapse}msec"

puts "----"
p b.map{|i| "#{i.z}:#{i.index}" }.join(", ")
```
