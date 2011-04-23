#!/usr/bin/perl

use warnings;

#DOCUMENTO OUTPUT
$output_file = "listing_code.tex";

#PASTA ORIGEM
$source_dir = $ARGV[0];

system("rm $output_file");

opendir(my $open_source_dir, $source_dir) || die "Impossivel abrir pasta oprigem!";

while(my $file = readdir $open_source_dir) {
    if(-f "$source_dir/$file" && ($file =~ m/.+\.cpp/ || $file =~ m/.+\.h/ )) {
        print $file, "\n";
        my $filename = $file;
        $filename =~ s/\_/\\\_/g;
        system("echo \"\\section*{$filename}\" >> $output_file");
        system("echo \"\\lstinputlisting{$source_dir$file}\" >> $output_file");
        system("echo \"\\pagebreak\" >> $output_file");
    }
}

close $source_dir;
